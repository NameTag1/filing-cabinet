#pragma once
#include "StateStack.h"
#include "ResourceHolder.h"
#include "Context.h"
#include "JsonHandler.h"

#include <SFML/Graphics.hpp>

class Application
{
public:
	Application();
	void RUN();
	void handleEvents();

private:
	StateStack mStateStack;
	int FPS;
	bool running;
	sf::RenderWindow mWindow;
	Context mContext;
	JsonHandler mJsonHandler;
};

