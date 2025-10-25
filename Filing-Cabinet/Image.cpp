#include "Image.h"

#include <SFML/Graphics.hpp>

Image::Image(sf::Texture texture, RelativeRect rect)
	: mSprite(texture), GUI_Object(rect)
{
}

bool Image::update(sf::FloatRect parrentRect)
{
	mRect.update(parrentRect);
	mRect.scaleSprite(mSprite);
	return false;
}

bool Image::draw(sf::RenderWindow* target)
{
	target->draw(mSprite);
	return false;
}
