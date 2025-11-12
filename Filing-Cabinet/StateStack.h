#pragma once
#include <vector>
#include "State.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Context.h"

#include "States.h" // For StateTypes enum

class StateStack
{
public:
	StateStack();
	void update();
	void handleEvent(const std::optional<sf::Event> event);
	void draw();

	void pushState(StateType type);
	void popState();
	void clearStates();

	void setContext(Context* context);

private:
	enum Actions {
		push,
		pop,
		clear
	};
	void RunActions();
	std::vector<std::pair<Actions, StateType>> mActionQueue;
	std::vector<State*> mStates;
	Context* mContext;
};

