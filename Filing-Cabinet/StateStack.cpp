#include "StateStack.h"

#include "Logger.h"

StateStack::StateStack()
{
}

void StateStack::update()
{
	for(auto & state : mStates) {
		if(!state.update()) {
			break; // If false is returned, stop updating further states
		}
	}
}

void StateStack::handleEvent(const std::optional<sf::Event> event)
{
	for(auto & state : mStates) {
		if(!state.handleEvent(event)) {
			break; // If false is returned, stop event handling of further states
		}
	}
}

void StateStack::draw(sf::RenderWindow* target)
{
	for(auto & state : mStates) {
		if(!state.draw(target)) {
			break; // If false is returned, stop drawing further states
		}
	}
}

void StateStack::pushState(StateTypes type)
{
	switch(type) {
		case Menue:
			// mStates.push_back(MenueState());
			Logger::Instance->LogData(Logger::Sys, "Pushed Menue State");
			break;
		case etc:
			// mStates.push_back(EtcState());
			Logger::Instance->LogData(Logger::Sys, "Pushed Menue State");
			break;
		default:
			// Handle unknown state type
			break;
	}
}

void StateStack::popState()
{
}

void StateStack::clearStates()
{
}
