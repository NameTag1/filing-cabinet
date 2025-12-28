#include "Button.h"

#include <SFML/Graphics.hpp>

Button::Button(sf::Texture* texture, sf::Texture* hoverTexture, RelativeRect rect)
	: mSprite(*texture), mHoverSprite(*hoverTexture), GUI_Object(rect) //Texture pointer passed because non-pointer parameter would self-destruct after construction
	, hoveredOver(false)
{
}

void Button::SetCallback(std::function<void()> callback)
{
	mCallback = callback;
}

bool Button::update(sf::FloatRect parrentRect)
{
	mRect.update(parrentRect);
	mRect.scaleSprite(mSprite);
	mRect.scaleSprite(mHoverSprite);
	setPosition(mRect.getRect().position);

	return false;
}

bool Button::handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window)
{
	if (!event.has_value() || window == nullptr) return false;

	if (const auto* mouseEvent = event->getIf<sf::Event::MouseMoved>()) {
		// Convert window pixel coords -> world coords
		sf::Vector2f mouseWorld = window->mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

		// Convert world coords into this object's local coords
		sf::Vector2f localPos = getInverseTransform().transformPoint(mouseWorld);

		// Local rect is (0,0) .. (width, height)
		const sf::FloatRect rectLocal({ 0.f, 0.f }, { mRect.getRect().size.x, mRect.getRect().size.y });

		if (rectLocal.contains(localPos)) {
			hoveredOver = true;
			return true;
		}
		else {
			hoveredOver = false;
		}
	}

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
				if (mCallback) mCallback();
				return true;
			}
		}
	}
	return false;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (hoveredOver) {
		target.draw(mHoverSprite, states);
	}
	else
	{
		target.draw(mSprite, states);
	}
}
