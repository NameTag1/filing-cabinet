#include "SettingsState.h"


SettingsState::SettingsState()
	: mContainer(RelativeRect(sf::FloatRect({ 0.5f, 0.5f }, { 0.6f, 0.8f })))
{
}

bool SettingsState::update() {
	sf::Vector2f viewSize = context->mWindow->getView().getSize();
	mContainer.update(sf::FloatRect({ 0.f, 0.f }, { viewSize.x, viewSize.y }));

	return false;
}

bool SettingsState::handleEvent(const std::optional<sf::Event> event) {
	// pass the window pointer so children can map pixel -> world coords
	mContainer.handleEvent(event, context->mWindow);
	return false;
}

bool SettingsState::draw() {
	context->mWindow->draw(mContainer);
	return false;
}