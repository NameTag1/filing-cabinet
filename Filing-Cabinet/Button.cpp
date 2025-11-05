#include "Button.h"

#include <SFML/Graphics.hpp>

Button::Button(sf::Texture* texture, RelativeRect rect)
	: mSprite(*texture), GUI_Object(rect) //Texture pointer passed because non-pointer parameter would self-destruct after construction
{
}

bool Button::update(sf::FloatRect parrentRect)
{
	mRect.update(parrentRect);
	mRect.scaleSprite(mSprite);

	return false;
}

void Button::draw(sf::RenderWindow* target, sf::RenderStates states) const
{
	target->draw(mSprite, states);
}
