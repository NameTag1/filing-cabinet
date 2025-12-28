#pragma once

#include "RelativeRect.h"
#include <SFML/Graphics/RenderWindow.hpp>

class GUI_Object : public sf::Drawable, public sf::Transformable
{
public:
	GUI_Object(RelativeRect mRect);
	virtual bool update(sf::FloatRect parrentRect);
	virtual bool handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window);

	virtual sf::FloatRect getRect();

protected:
	RelativeRect mRect;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

