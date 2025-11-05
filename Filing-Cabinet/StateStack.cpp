#include "StateStack.h"

#include "Logger.h"
#include "MenuState.h"

StateStack::StateStack()
{
}

void StateStack::update()
{
	for(auto & state : mStates) {
		if(!state->update()) {
			break; // If false is returned, stop updating further states
		}
	}
}

void StateStack::handleEvent(const std::optional<sf::Event> event)
{
	for(auto & state : mStates) {
		if(!state->handleEvent(event)) {
			break; // If false is returned, stop event handling of further states
		}
	}
}

void StateStack::draw(sf::RenderWindow* target)
{
	for(auto & state : mStates) {
		if(!state->draw(target)) {
			break; // If false is returned, stop drawing further states
		}
	}
}

void StateStack::pushState(StateType type)
{
	switch(type) {
		case Menu:
			mStates.push_back(new MenuState());
			mContext->mLogger->LogData(Logger::Sys, "Pushed Menu State");
			break;
		default:
			// Handle unknown state type
			break;
	}
}

void StateStack::popState()
{
	mStates.pop_back();
}

void StateStack::clearStates()
{
	mStates.clear();
}

void StateStack::setContext(Context* context)
{
	mContext = context;
	State::setContext(context);
}
