#pragma once

#include "RelativeRect.h"
#include "GUI_Object.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Container : public GUI_Object
{
public:
	Container(RelativeRect rect);
	void pushObject(std::unique_ptr<GUI_Object> object);

	virtual bool update(sf::FloatRect parentRect);
	virtual bool handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::vector<std::unique_ptr<GUI_Object>> mObjects;
};

