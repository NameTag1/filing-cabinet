#include "MenuState.h"

#include "ResourceHolder.h"
#include "Image.h"

MenuState::MenuState()
	: mContainer(RelativeRect(sf::FloatRect({ 0, 0 },{ 1, 1 })))
{
	context->mTextureHolder->loadResource("Resources/Button.png", "Button");
	mContainer.pushObject(std::make_unique<Image>(
		context->mTextureHolder->getResource("Button"),
		RelativeRect(sf::FloatRect({0.5f, 0.5f}, {0.5f, 0.5f}), RelativeWH::Normal, Anchor::TL)
	));
}

bool MenuState::update() {
	sf::Vector2f viewSize = context->mWindow->getView().getSize();
	mContainer.update(sf::FloatRect({ 0.f, 0.f }, { viewSize.x, viewSize.y }));

	context->mLogger->LogData(Logger::Sys, std::to_string(viewSize.x));

	return false;
}

bool MenuState::handleEvent(const std::optional<sf::Event> event) {
	mContainer.handleEvent(event);
	return false;
}

bool MenuState::draw(sf::RenderWindow* target) {
	target->draw(mContainer);
	return false;
}
