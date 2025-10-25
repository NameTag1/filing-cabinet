#pragma once
#include <vector>
#include "State.h"
#include "SFML/Graphics/RenderWindow.hpp"

class StateStack
{
public:
	enum StateTypes{
		Menue,
		etc
	};

	StateStack();
	void update();
	void handleEvent(const std::optional<sf::Event> event);
	void draw(sf::RenderWindow* target);

	void pushState(StateTypes type);
	void popState();
	void clearStates();

private:
	std::vector<State> mStates;
};

