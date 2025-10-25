#include "MenuState.h"

#include "ResourceHolder.h"
#include "Image.h"

MenuState::MenuState()
	: mContainer(RelativeRect(sf::FloatRect({0,0},{1,1})))
{
	ResourceHolder::getInstance()->loadTexture("Resources/Button.png", "Button");
	mContainer.pushObject(std::make_unique<Image>(
		*ResourceHolder::getInstance()->getTexture("Button"),
		RelativeRect(sf::FloatRect({0.25f, 0.25f}, {0.5f, 0.5f}), RelativeWH::Normal, Anchor::Center)
	));
}

bool MenuState::update() {
	//mContainer.update(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	return false;
}

bool MenuState::handleEvent(const std::optional<sf::Event> event) {
	mContainer.handleEvent(event);
	return false;
}

bool MenuState::draw(sf::RenderWindow* target) {
	mContainer.draw(target);
	return false;
}
