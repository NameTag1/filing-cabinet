#pragma once

#include "State.h"
#include "Container.h"

class NewDocumentState : public State
{
public:
	NewDocumentState();

	virtual bool update();
	virtual bool handleEvent(const std::optional<sf::Event> event);
	virtual bool draw();

private:
	Container mContainer;
};

