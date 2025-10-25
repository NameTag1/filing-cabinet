#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

class StateStack; //Psuedo forward declaration

class State
{
public:
	State();
	static void setParrent(StateStack* p);
	
	virtual bool update();
	virtual bool handleEvent(const std::optional<sf::Event> event);
	virtual bool draw(sf::RenderWindow* target);
	
	void push();
	void pop();

private:
	static StateStack* parrent;
};

