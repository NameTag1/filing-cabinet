#include "Image.h"

#include <SFML/Graphics.hpp>

Image::Image(sf::Texture* texture, RelativeRect rect)
	: mSprite(*texture), GUI_Object(rect) //Texture pointer passed because non-pointer parameter would self-destruct after construction
{
}

bool Image::update(sf::FloatRect parrentRect)
{
	mRect.update(parrentRect);
	mRect.scaleSprite(mSprite);
	return false;
}

bool Image::draw(sf::RenderTarget* target, sf::RenderStates states)
{
	target->draw(mSprite);
	return false;
}
