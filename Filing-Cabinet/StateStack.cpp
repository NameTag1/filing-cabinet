#include "StateStack.h"

#include "Logger.h"
#include "MenuState.h"
#include "NewDocumentState.h"
#include "States.h"

StateStack::StateStack()
	: mContext(nullptr)
{
	State::setParrent(this);
}

void StateStack::update()
{
	RunActions();
	
	for (auto itr = mStates.rbegin(); itr != mStates.rend(); ++itr){
		if(!(*itr)->update()) {
			break; // If false is returned, stop updating further states
		}
	}
}

void StateStack::handleEvent(const std::optional<sf::Event> event)
{
	for (auto itr = mStates.rbegin(); itr != mStates.rend(); ++itr) {
		if (!(*itr)->handleEvent(event)) {
			break; // If false is returned, stop event handling of further states
		}
	}
}

void StateStack::draw()
{
	for (auto itr = mStates.rbegin(); itr != mStates.rend(); ++itr) {
		if (!(*itr)->draw()) {
			break; // If false is returned, stop drawing further states
		}
	}
}

void StateStack::pushState(StateType type)
{
	mActionQueue.push_back(std::pair(Actions::push, type));
}

void StateStack::popState()
{
	mActionQueue.push_back(std::pair(Actions::pop, StateType::Null));
}

void StateStack::clearStates()
{
	mActionQueue.push_back(std::pair(Actions::clear, StateType::Null));
}

bool StateStack::isEmpty() const
{
	return mStates.empty();
}

void StateStack::setContext(Context* context)
{
	mContext = context;
	State::setContext(context);
}

void StateStack::RunActions()
{
	for (auto& i : mActionQueue) {
		if (i.first == Actions::clear) {
			mStates.clear();
			Logger::Instance->LogData(Logger::Sys, "States Cleared");
		}
		else if (i.first == Actions::pop) {
			mStates.pop_back();
			Logger::Instance->LogData(Logger::Sys, "State Popped");
		}
		else if (i.first == Actions::push) {
			switch (i.second) {
			case Menu:
				mStates.push_back(new MenuState());
				Logger::Instance->LogData(Logger::Sys, "Pushed Menu State");
				break;
			case NewDocState:
				mStates.push_back(new NewDocumentState());
				Logger::Instance->LogData(Logger::Sys, "Pushed NewDocumentState State");
				break;
			default:
				// Handle unknown state type
				Logger::Instance->LogData(Logger::Sys, "Unknown State Attempted to Push");
				break;
			}
		}
	}
	mActionQueue.clear();
}
