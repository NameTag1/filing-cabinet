#include "Sidebar.h"

Sidebar::Sidebar(sf::Texture* closedTexture, sf::Texture* openTexture, RelativeRect closedRect, RelativeRect openRect)
	: GUI_Object(closedRect)
	, mClosedSprite(*closedTexture)
	, mOpenSprite(*openTexture)
	, mCloseRect(closedRect)
	, mOpenRect(openRect)
	, mOpen(false)
{
}

bool Sidebar::update(sf::FloatRect parrentRect)
{
	if (mOpen) {
		mRect.setRect(mOpenRect.getRelativeRect());
		mRect.update(parrentRect);
		mRect.scaleSprite(mOpenSprite);
		mOpenDelay = mOpen;
	}
	if (!mOpen) {
		mRect.setRect(mCloseRect.getRelativeRect());
		mRect.update(parrentRect);
		mRect.scaleSprite(mClosedSprite);
		mOpenDelay = mOpen;
	}
	setPosition(mRect.getRect().position);
	return false;
}

bool Sidebar::handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window)
{
	if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonReleased>()) {
		if (mouseEvent->button == sf::Mouse::Button::Left)
		{
			// Convert window pixel coords -> world coords
			sf::Vector2f mouseWorld = window->mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

			// Convert world coords into this object's local coords
			sf::Vector2f localPos = getInverseTransform().transformPoint(mouseWorld);

			// Local rect is (0,0) .. (width, height)
			const sf::FloatRect rectLocal({ 0.f, 0.f }, { mRect.getRect().size.x, mRect.getRect().size.y });

			if (rectLocal.contains(localPos)) {
				mOpen = !mOpen;
				return true;
			}
		}
	}
	return false;
}

void Sidebar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (mOpenDelay) {
		target.draw(mOpenSprite, states);
		target.draw(*mChild, states);
	}
	else
	{
		target.draw(mClosedSprite, states);
	}
}

void Sidebar::setChild(std::unique_ptr<Container> child) {
	mChild = std::move(child);
};