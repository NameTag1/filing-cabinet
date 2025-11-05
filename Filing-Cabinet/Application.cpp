#include "Application.h"
#include "Logger.h"

#include "rapidjson/writer.h"
#include "States.h"

Application::Application()
	: FPS(60)
	, running(true)
	, mWindow(sf::VideoMode({ 1200, 900 }), "Filing Cabinet")
{
	mContext.mWindow = &mWindow;
	mContext.mLogger = new Logger;
	mContext.mTextureHolder = new TextureHolder();
	mContext.mFontHolder = new FontHolder();

	mContext.mLogger->LogData(Logger::Sys, "Application Initialized");

	mStateStack.setContext(&mContext);
}

void Application::RUN()
{
	mWindow.setVerticalSyncEnabled(true); //Sets frame rate to monitor refresh rate
	mStateStack.pushState(StateType::Menu);

	while (running) {
		mWindow.clear({ 92, 255, 92 });

		mStateStack.update();
		handleEvents();
		mStateStack.draw(&mWindow);

		mWindow.display();
	}
	mWindow.close();
	mContext.mLogger->LogData(Logger::Sys, "Window Closed");
}

void Application::handleEvents()
{
	while (const std::optional<sf::Event> event = mWindow.pollEvent())
	{
		if (event->is<sf::Event::Closed>()) {
			running = false;
			mContext.mLogger->LogData(Logger::Sys, "Stopping...");
			break;
		}
		else {
			mStateStack.handleEvent(event);
		}
	}
}
