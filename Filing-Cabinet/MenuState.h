#pragma once

#include "State.h"
#include "Container.h"

class MenuState : public State
{
public:
	MenuState();

	virtual bool update();
	virtual bool handleEvent(const std::optional<sf::Event> event);
	virtual bool draw(sf::RenderWindow* target);

private:
	Container mContainer;
};

