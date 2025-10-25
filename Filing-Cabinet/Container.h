#pragma once

#include "RelativeRect.h"
#include "GUI_Object.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Container
{
public:
	Container(RelativeRect rect);
	void pushObject(std::unique_ptr<GUI_Object> object);

	void update(sf::FloatRect parrentRect);
	void handleEvent(const std::optional<sf::Event> event);
	void draw(sf::RenderWindow* target);

private:
	RelativeRect mRect;
	std::vector<std::unique_ptr<GUI_Object>> mObjects;
};

