#pragma once

#include "RelativeRect.h"
#include <SFML/Graphics/RenderWindow.hpp>

class GUI_Object
{
public:
	GUI_Object(RelativeRect mRect);
	virtual bool update(sf::FloatRect parrentRect);
	virtual bool handleEvent(const std::optional<sf::Event> event);
	virtual bool draw(sf::RenderWindow* target);

protected:
	RelativeRect mRect;

};

