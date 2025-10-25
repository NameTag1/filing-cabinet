#include "State.h"

StateStack* State::parrent = nullptr; // Initialize static member

State::State()
{
}

void State::setParrent(StateStack* p)
{
	parrent = p;
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

void State::push()
{
	
}

void State::pop()
{
}
