#include "Application.h"
#include "Logger.h"
#include "Constants.h"

#include "States.h"
#include <optional>
#include "ResourceHolder.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

Application::Application()
	: FPS(60)
	, running(true)
	, mWindow(sf::VideoMode({ 1, 1 }), "Filing Cabinet") //Not Zero, otherwise would mess up rects
	, mOCR()
{
	mContext.mWindow = &mWindow;
	mContext.mTextureHolder = new TextureHolder();
	mContext.mFontHolder = new FontHolder();

	Logger::Instance->LogData(Logger::Sys, "Application Initialized");

	mContext.mFontHolder->loadResource("resources/montserrat/Montserrat-Regular.ttf", "Main");

	mJsonHandler.openJson("settings", "Data/settings.json");

	mWindow.setSize({ mJsonHandler.DATA["settings"]["Window"]["ScreenW"],mJsonHandler.DATA["settings"]["Window"]["ScreenH"] });
	mWindow.setPosition({ mJsonHandler.DATA["settings"]["Window"]["ScreenX"],mJsonHandler.DATA["settings"]["Window"]["ScreenY"] });

	//Initialize Constants, don't save object created.
	Constants z(mJsonHandler.DATA["settings"]);

	// Ensure the view matches the window size so layout and event coords align
	mWindow.setView(sf::View(sf::FloatRect(
		{ 0.f, 0.f },
		{ static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y) }
		)));

	mStateStack.setContext(&mContext);
}

void Application::RUN()
{
	mWindow.setVerticalSyncEnabled(true); //Sets frame rate to monitor refresh rate
	mStateStack.pushState(StateType::Menu);

	while (running) {

		mStateStack.update();
		handleEvents();

		mWindow.clear({ 92, 255, 92 });
		mStateStack.draw();

		mWindow.display();

		running = (mStateStack.isEmpty()) ? false : running; //If empty, stop running
	}

	//Save Window Size Preferance 
	mJsonHandler.DATA["settings"]["Window"]["ScreenW"] = mWindow.getSize().x;
	mJsonHandler.DATA["settings"]["Window"]["ScreenH"] = mWindow.getSize().y;
	mJsonHandler.DATA["settings"]["Window"]["ScreenX"] = mWindow.getPosition().x;
	mJsonHandler.DATA["settings"]["Window"]["ScreenY"] = mWindow.getPosition().y;
	mJsonHandler.writeAll();
	mJsonHandler.closeAll();
	Logger::Instance->LogData(Logger::Sys, "JsonHandler Closed");

	/*mOCR.addToScanQueue("1Data.png");*/

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
		else if (event->is<sf::Event::Resized>()) {
			// Keep the default view size equal to the window size so drawing and input coordinates stay aligned.
			const float newWidth = static_cast<float>(mWindow.getSize().x);
			const float newHeight = static_cast<float>(mWindow.getSize().y);
			mWindow.setView(sf::View(sf::FloatRect({ 0.f, 0.f }, { newWidth, newHeight })));
		}
		else {
			mStateStack.handleEvent(event);
		}
	}
}
