#pragma once

#include "State.h"
#include "Container.h"

class SettingsState : public State
{
public:
	SettingsState();

	virtual bool update();
	virtual bool handleEvent(const std::optional<sf::Event> event);
	virtual bool draw();


private:
	Container mContainer;
};

