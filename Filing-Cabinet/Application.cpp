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
	sf::Clock mClock;
	sf::Time mTime = std::chrono::milliseconds(0);
	sf::Time mRefreshRate = std::chrono::milliseconds(50);
	
	while (running) {
		mTime += mClock.restart();
		while (mTime > mRefreshRate) {
			mTime -= mRefreshRate;
			Logger::Instance->LogData(Logger::Action, "Loop");
			handleEvents();
		}
	}
	mWindow.close();
	Logger::Instance->LogData(Logger::Sys, "Window Closed");
}

void Application::handleEvents()
{
	while (const std::optional event = mWindow.pollEvent())
	{
		if (event->is<sf::Event::Closed>()) {
			running = false;
			Logger::Instance->LogData(Logger::Sys, "Stopping...");
		}
	}
}
