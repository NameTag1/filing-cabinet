#include "GUI_Object.h"

GUI_Object::GUI_Object(RelativeRect mRect)
	: mRect(mRect)
{
}

bool GUI_Object::update(sf::FloatRect parrentRect) {
	return false;
}

bool GUI_Object::handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window) {
	return false;
}

void GUI_Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {

};

sf::FloatRect GUI_Object::getRect() {
	return mRect.getRect();
}