#include "MenuState.h"

#include "ResourceHolder.h"
#include "Image.h"
#include "Button.h"

MenuState::MenuState()
	: mContainer(RelativeRect(sf::FloatRect({ 0.f, 0.f },{ 1.f, 1.f })))
{
	context->mTextureHolder->loadResource("Resources/Button.png", "Button");
	context->mTextureHolder->loadResource("Resources/Upper_Bar.png", "Menu Bar");
	
	//Top Menu Bar
	mContainer.pushObject(std::make_unique<Image>(
		context->mTextureHolder->getResource("Menu Bar"),
		RelativeRect(sf::FloatRect({0.f, 0.f}, {1.f, 0.05f}), RelativeWH::Normal, Anchor::TL)
	));

	//Quit Button
	std::unique_ptr<Button> fileButton = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		RelativeRect(sf::FloatRect({ 0.f, 0.f }, { 0.2f, 0.05f }), RelativeWH::Normal, Anchor::TL)
	);
	fileButton->SetCallback([this]() {
		context->mLogger->LogData(Logger::Action, "Button Pressed!");
		this->push(StateType::Menu);
		});
	mContainer.pushObject(std::move(fileButton));

	//Quit Button
	std::unique_ptr<Button> exitButton = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		RelativeRect(sf::FloatRect({ 1.f, 0.0f }, { 0.2f, 0.05f }), RelativeWH::Normal, Anchor::TR)
	);
	exitButton->SetCallback([this]() {
		context->mLogger->LogData(Logger::Action, "Button Pressed!");
		this->clear();
	});
	mContainer.pushObject(std::move(exitButton));
}

bool MenuState::update() {
	sf::Vector2f viewSize = context->mWindow->getView().getSize();
	mContainer.update(sf::FloatRect({ 0.f, 0.f }, { viewSize.x, viewSize.y }));

	return false;
}

bool MenuState::handleEvent(const std::optional<sf::Event> event) {
	// pass the window pointer so children can map pixel -> world coords
	mContainer.handleEvent(event, context->mWindow);
	return false;
}

bool MenuState::draw() {
	context->mWindow->draw(mContainer);
	return false;
}
