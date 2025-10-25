#pragma once

#include "GUI_Object.h"

class Image : public GUI_Object
{
public:
	Image(sf::Texture texture, RelativeRect rect);

	virtual bool update(sf::FloatRect parrentRect) override;
	virtual bool draw(sf::RenderWindow* target) override;

private:
	sf::Sprite mSprite;
};

