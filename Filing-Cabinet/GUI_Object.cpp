#include "GUI_Object.h"

#include "Container.h"

GUI_Object::GUI_Object(RelativeRect mRect)
	: mRect(mRect)
	, mParrent(nullptr)
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

RelativeRect* GUI_Object::getRelativeRect()
{
	return &mRect;
}

void GUI_Object::setParrent(GUI_Object* container) {
	mParrent = container;
}

sf::Transform GUI_Object::getWorldTransform()
{
	if (mParrent == nullptr)
		return getTransform();
	else
		return mParrent->getWorldTransform() * getTransform();
}
