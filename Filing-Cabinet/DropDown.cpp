#include "DropDown.h"

#include "Logger.h"
#include "Sidebar.h"
#include <algorithm>

DropDown::DropDown(sf::Texture* texture, RelativeRect rect, Side side)
	: mSprite(*texture)
	, focus(false)
	, GUI_Object(rect)
	, mSide(side)
{
}

bool DropDown::update(sf::FloatRect parrentRect)
{
	mRect.update(parrentRect);
	mRect.scaleSprite(mSprite);
	setPosition(mRect.getRect().position);

	// If there's no child, nothing more to do
	if (!mChild) return false;

	mChild->update(parrentRect);
	
	//Logger::Instance->LogData(Logger::LogType::Sys, "DropDown Child Abs Pos: " + std::to_string(childAbsPos.x) + ", " + std::to_string(childAbsPos.y));

	return false;
}

bool DropDown::handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window)
{
	if (!event.has_value() || window == nullptr) return false;

	if (focus) {
		if (mChild->handleEvent(event, window)) {
			//If child is being hovered over, focus maintained
			focus = true;
			return true;
		}
	}

	// Check mouse moved specifically to set focus when hovering over button OR child.
	if (const auto* mouseEvent = event->getIf<sf::Event::MouseMoved>()) {
		// Convert window pixel coords -> world coords
		sf::Vector2f mouseWorld = window->mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

		// Convert world coords into this object's local coords
		sf::Vector2f localPos = GUI_Object::getWorldTransform().getInverse().transformPoint(mouseWorld);

		// Local rect is (0,0) .. (width, height)
		const sf::FloatRect rectLocal({ 0.f, 0.f }, { mRect.getRect().size.x, mRect.getRect().size.y });

		// If over button OR over child, keep focus
		if (rectLocal.contains(localPos)) {
			focus = true;
			return true;
		}
		else {
			focus = false;
		}
	}

	//Run twice for safety
	if (focus) {
		if (mChild->handleEvent(event, window)) {
			//If child is being hovered over, focus maintained
			focus = true;
			return true;
		}
	}

	return false;
}

void DropDown::setChild(std::unique_ptr<Container> child)
{
	mChild = std::move(child);
	mChild->getRelativeRect()->shiftRect(sf::FloatRect({mRect.getRelativeRect().position.x, mRect.getRelativeRect().position.y + mRect.getRelativeRect().size.y}, {0, 0}));
}

void DropDown::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw child using absolute coordinates (child position set in update).
	if (focus && mChild) {
		target.draw(*mChild, states);
	}

	// Then draw the DropDown's sprite at its local transform.
	states.transform *= getTransform();
	target.draw(mSprite, states);
}
