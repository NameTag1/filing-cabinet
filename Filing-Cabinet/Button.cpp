#include "Button.h"

#include <SFML/Graphics.hpp>

Button::Button(sf::Texture* texture, RelativeRect rect)
	: mSprite(*texture), GUI_Object(rect) //Texture pointer passed because non-pointer parameter would self-destruct after construction
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
	setPosition(mRect.getRect().position);

	return false;
}

bool Button::handleEvent(const std::optional<sf::Event> event)
{
	return false;
}

void Button::activate()
{
	mCallback();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}
