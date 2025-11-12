#pragma once

#include "GUI_Object.h"

class Image : public GUI_Object
{
public:
	Image(sf::Texture* texture, RelativeRect rect);

	virtual bool update(sf::FloatRect parrentRect) override;
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite mSprite;
};

