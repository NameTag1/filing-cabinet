#include "MenuState.h"

#include "ResourceHolder.h"
#include "Image.h"
#include "Button.h"

MenuState::MenuState()
	: mContainer(RelativeRect(sf::FloatRect({ 0.f, 0.f },{ 1.f, 1.f })))
{
	context->mTextureHolder->loadResource("Resources/Button.png", "Button");
	/*mContainer.pushObject(std::make_unique<Image>(
		context->mTextureHolder->getResource("Button"),
		RelativeRect(sf::FloatRect({0.5f, 0.5f}, {0.25f, 0.2f}), RelativeWH::Normal, Anchor::Center)
	));*/

	std::unique_ptr<Button> exitButton = std::make_unique<Button>(
		context->mTextureHolder->getResource("Button"),
		RelativeRect(sf::FloatRect({ 0.0f, 0.0f }, { 0.25f, 0.2f }), RelativeWH::Normal, Anchor::TL)
	);
	exitButton->SetCallback([this]() {
		context->mLogger->LogData(Logger::Action, "Button Pressed!");
		this->push(StateType::Menu);
	});
	mContainer.pushObject(std::move(exitButton));
}

bool MenuState::update() {
	sf::Vector2f viewSize = context->mWindow->getView().getSize();
	mContainer.update(sf::FloatRect({ 0.f, 0.f }, { viewSize.x, viewSize.y }));

	return false;
}

bool MenuState::handleEvent(const std::optional<sf::Event> event) {
	mContainer.handleEvent(event);
	return false;
}

bool MenuState::draw() {
	context->mWindow->draw(mContainer);
	return false;
}
