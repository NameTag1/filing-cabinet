#include "StateStack.h"

#include "Logger.h"
#include "MenuState.h"

StateStack::StateStack()
{
	State::setParrent(this);
}

void StateStack::update()
{
	RunActions();
	
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

void StateStack::draw()
{
	for(auto & state : mStates) {
		if(!state->draw()) {
			break; // If false is returned, stop drawing further states
		}
	}
}

void StateStack::pushState(StateType type)
{
	mActionQueue.push_back(std::pair(Actions::push, type));
	mContext->mLogger->LogData(Logger::Sys, "Pushed Menu State");
	
}

void StateStack::popState()
{
	mActionQueue.push_back(std::pair(Actions::pop, StateType::Null));
}

void StateStack::clearStates()
{
	mActionQueue.push_back(std::pair(Actions::pop, StateType::Null));
}

void StateStack::setContext(Context* context)
{
	mContext = context;
	State::setContext(context);
}

void StateStack::RunActions()
{
	for (auto i : mActionQueue) {
		if (i.first == Actions::clear) {
			mStates.clear();
		}
		else if (i.first == Actions::pop) {
			mStates.pop_back();
		}
		else if (i.first == Actions::push) {
			switch (i.second) {
			case Menu:
				mStates.push_back(new MenuState());
				mContext->mLogger->LogData(Logger::Sys, "Pushed Menu State");
				break;
			default:
				// Handle unknown state type
				mContext->mLogger->LogData(Logger::Sys, "Unknown State Pushed");
				break;
			}
		}
	}
	mActionQueue.clear();
}
