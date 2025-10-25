#include "Application.h"
#include "Logger.h"

#include "rapidjson/writer.h"

Application::Application()
	: FPS(60)
	, running(true)
	, mWindow(sf::VideoMode({ 800, 600 }), "Filing Cabinet")
{
	Logger::Instance->LogData(Logger::Sys, "Application Initialized");
}

void Application::RUN()
{
	mWindow.setVerticalSyncEnabled(true); //Sets frame rate to monitor refresh rate
	mStateStack.pushState(StateStack::Menue);
	while (running) {
		mWindow.clear({ 92, 255, 92 });

		mStateStack.update();
		handleEvents();
		mStateStack.draw(&mWindow);

		mWindow.display();
	}
	mWindow.close();
	Logger::Instance->LogData(Logger::Sys, "Window Closed");
}

void Application::handleEvents()
{
	while (const std::optional<sf::Event> event = mWindow.pollEvent())
	{
		if (event->is<sf::Event::Closed>()) {
			running = false;
			Logger::Instance->LogData(Logger::Sys, "Stopping...");
			break;
		}
		else {
			mStateStack.handleEvent(event);
		}
	}
}
