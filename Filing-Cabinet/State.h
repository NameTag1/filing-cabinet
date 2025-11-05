#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "Context.h"
#include "States.h"

class StateStack; //Psuedo forward declaration

class State
{
public:
	State();
	static void setParrent(StateStack* p);
	static void setContext(Context* c);
	
	virtual bool update();
	virtual bool handleEvent(const std::optional<sf::Event> event);
	virtual bool draw(sf::RenderWindow* target);
	
	void push(StateType type);
	void pop();
	void clear();

protected:
	static Context* context;

private:
	static StateStack* parrent;
};

