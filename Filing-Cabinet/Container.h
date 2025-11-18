#pragma once

#include "RelativeRect.h"
#include "GUI_Object.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Container : public sf::Drawable, public sf::Transformable
{
public:
	Container(RelativeRect rect);
	void pushObject(std::unique_ptr<GUI_Object> object);

	void update(sf::FloatRect parentRect);
	void handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	RelativeRect mRect;
	std::vector<std::unique_ptr<GUI_Object>> mObjects;
};

