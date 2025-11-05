#include "State.h"

#include "StateStack.h"

StateStack* State::parrent = nullptr; // Initialize static member
Context* State::context = nullptr; // Initialize static member

State::State()
{
}

void State::setParrent(StateStack* p)
{
	parrent = p;
}

void State::setContext(Context* c)
{
	context = c;
}

bool State::update()
{
	return false;
}

bool State::handleEvent(const std::optional<sf::Event> event)
{
	return false;
}

bool State::draw(sf::RenderWindow* target)
{
	return false;
}

void State::push(StateType type)
{
	parrent->pushState(type);
}

void State::pop()
{
	parrent->popState();
}

void State::clear()
{
	parrent->clearStates();
}
