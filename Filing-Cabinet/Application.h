#pragma once
#include "StateStack.h"
#include "Context.h"
#include "JsonHandler.h"
#include "OCR_Wrapper.h"

#include <SFML/Graphics/RenderWindow.hpp>

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
	OCR_Wrapper mOCR;
};

