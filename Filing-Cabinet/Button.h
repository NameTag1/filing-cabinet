#pragma once

#include "GUI_Object.h"

class Button : public GUI_Object
{
public:
	Button(sf::Texture* texture, RelativeRect rect);

	virtual bool update(sf::FloatRect parrentRect) override;
	
private:
	virtual void draw(sf::RenderWindow* target, sf::RenderStates states) const override;

private:
	sf::Sprite mSprite;
};
