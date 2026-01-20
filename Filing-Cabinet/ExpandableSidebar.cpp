#include "ExpandableSidebar.h"
#include <SFML/Window/Cursor.hpp>
#include <cmath>

ExpandableSidebar::ExpandableSidebar(sf::Texture* texture, RelativeRect rect, Edge edge, float minWidthPx)
	: GUI_Object(rect)
	, mSprite(*texture)
	, mChild(nullptr)
	, mEdge(edge)
	, mDragging(false)
	, mHandleThicknessPx(8.f)
	, mMinWidthPx(minWidthPx)
	, mHandCursorLoaded(false)
	, mArrowCursorLoaded(false)
	, mCursorSetToHand(false)
	, mHandCursor(sf::Cursor::Type::Hand)
	, mArrowCursor(sf::Cursor::Type::Arrow)
{
}

bool ExpandableSidebar::update(sf::FloatRect parrentRect)
{
	// Update our relative rect -> absolute rect, scale sprite, set transform position
	mRect.update(parrentRect);
	mRect.scaleSprite(mSprite);
	setPosition(mRect.getRect().position);

	// Update child using our absolute rect so it lays out inside the sidebar
	if (mChild) {
		mChild->update(mRect.getRect());
	}

	return false;
}

bool ExpandableSidebar::handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window)
{
	if (!event.has_value() || window == nullptr) return false;

	// Utility: get mouse world coordinate
	auto mousePixelPos = [&event]() -> sf::Vector2i {
		if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>()) return { mb->position.x, mb->position.y };
		if (const auto* mb = event->getIf<sf::Event::MouseButtonReleased>()) return { mb->position.x, mb->position.y };
		if (const auto* mm = event->getIf<sf::Event::MouseMoved>()) return { mm->position.x, mm->position.y };
		return { -1, -1 };
	}();

	sf::Vector2f mouseWorld = window->mapPixelToCoords(mousePixelPos);

	// Make a small world-space handle thickness from pixel thickness (accounts for view scaling)
	sf::Vector2f world0 = window->mapPixelToCoords({ 0,0 });
	sf::Vector2f world1 = window->mapPixelToCoords({ 1,0 });
	float worldPerPixelX = world1.x - world0.x;
	float worldHandle = mHandleThicknessPx * std::fabs(worldPerPixelX);

	const sf::FloatRect absRect = mRect.getRect(); // absolute rect from last update: position, size in world coords

	// Handle hover cursor on mouse move (only when not currently dragging)
	if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>()) {
		// Determine inner edge world X
		float innerEdgeX = (mEdge == Edge::Right) ? absRect.position.x : (absRect.position.x + absRect.size.x);
		float dy = mouseWorld.y - absRect.position.y;
		bool withinVertical = (dy >= 0.f && dy <= absRect.size.y);

		bool hoveringHandle = withinVertical && std::fabs(mouseWorld.x - innerEdgeX) <= worldHandle;

		// If hovering handle, set hand cursor; otherwise set arrow cursor (only if we changed it before)
		if (hoveringHandle) {
			if (!mCursorSetToHand && mHandCursorLoaded) {
				window->setMouseCursor(mHandCursor);
				mCursorSetToHand = true;
			}
		}
		else {
			if (mCursorSetToHand && mArrowCursorLoaded) {
				window->setMouseCursor(mArrowCursor);
				mCursorSetToHand = false;
			}
		}

		// If not dragging, don't consume the event here (allow others to react), but indicate handled if hovering
		if (hoveringHandle) return true;
	}

	// If releasing mouse, stop dragging
	if (const auto* mouseRel = event->getIf<sf::Event::MouseButtonReleased>()) {
		if (mouseRel->button == sf::Mouse::Button::Left) {
			if (mDragging) {
				mDragging = false;
				// ensure cursor reset after dragging ends
				if (mCursorSetToHand && mArrowCursorLoaded) {
					window->setMouseCursor(mArrowCursor);
					mCursorSetToHand = false;
				}
				return true;
			}
		}
		return false;
	}

	// Start dragging when pressing on the inner edge hit zone
	if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) {
		if (mousePress->button == sf::Mouse::Button::Left) {
			// Determine inner edge world X
			float innerEdgeX = (mEdge == Edge::Right) ? absRect.position.x : (absRect.position.x + absRect.size.x);
			float dy = mouseWorld.y - absRect.position.y;
			bool withinVertical = (dy >= 0.f && dy <= absRect.size.y);

			if (withinVertical && std::fabs(mouseWorld.x - innerEdgeX) <= worldHandle) {
				mDragging = true;
				// Ensure hand cursor when starting drag
				if (!mCursorSetToHand && mHandCursorLoaded) {
					window->setMouseCursor(mHandCursor);
					mCursorSetToHand = true;
				}
				return true;
			}
		}
		return false;
	}

	// Handle mouse move while dragging
	if (mDragging) {
		// Parent width (assume sidebar's parent is the view area; this matches how other containers are used)
		const sf::Vector2f viewSize = window->getView().getSize();
		const float parentWidth = viewSize.x;
		const float parentHeight = viewSize.y;

		// Compute new width in world coords depending on edge.
		float newWidthPx = absRect.size.x;

		if (mEdge == Edge::Right) {
			// For right-anchored sidebar the width is distance from mouse to right edge of view
			newWidthPx = parentWidth - mouseWorld.x;
		}
		else { // Left edge anchored
			// Width is distance from left edge of view (0) to mouse x
			newWidthPx = mouseWorld.x;
		}

		// Clamp to sensible range
		if (newWidthPx < mMinWidthPx) newWidthPx = mMinWidthPx;
		if (newWidthPx > parentWidth - 8.f) newWidthPx = parentWidth - 8.f;

		// Convert to relative w (fractions used by RelativeRect)
		float newRelW = newWidthPx / parentWidth;

		// Preserve existing relative x,y,h
		sf::FloatRect rel = mRect.getRelativeRect(); // x,y,w,h (fractions)
		// Update only width fraction; RelativeRect::setRect expects position/size as (x,y,w,h)
		rel.size.x = newRelW;

		mRect.setRect(rel);
		// Immediately update absolute rect to reflect change so subsequent events/readers see updated values
		mRect.update(sf::FloatRect({ 0.f,0.f }, { parentWidth, parentHeight }));
		setPosition(mRect.getRect().position);
		// update child to new size
		if (mChild) mChild->update(mRect.getRect());
		return true;
	}

	return false;
}

void ExpandableSidebar::setChild(std::unique_ptr<Container> child)
{
	mChild = std::move(child);
}

void ExpandableSidebar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	if (mChild) {
		target.draw(*mChild, states);
	}
}