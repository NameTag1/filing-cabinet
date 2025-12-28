#include "Container.h"

Container::Container(RelativeRect rect)
	: GUI_Object(rect)
{
}

void Container::pushObject(std::unique_ptr<GUI_Object> object)
{
	mObjects.push_back(std::move(object));
}

bool Container::update(sf::FloatRect parentRect) {
	mRect.update(parentRect); //Update own rect based on parrent rect BEFORE updating children
	setPosition(mRect.getRect().position);

	sf::FloatRect currentRect = mRect.getRect();
	for(auto& object : mObjects) {
		object->update(currentRect);
	}

	return false;
}

bool Container::handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window) {
	for (auto& object : mObjects) {
		if (object->handleEvent(event, window)) {
			return true;
		};
	}

	return false;
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	for (auto& object : mObjects) {
		target.draw(*object, states);
	}
}