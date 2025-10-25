#include "Container.h"

Container::Container(RelativeRect rect)
	: mRect(rect)
{
}

void Container::pushObject(std::unique_ptr<GUI_Object> object)
{
	mObjects.push_back(move(object));
}

void Container::update(sf::FloatRect parrentRect) {
	for(auto& object : mObjects) {
		object->update(mRect.getRect());
	}
};

void Container::handleEvent(const std::optional<sf::Event> event) {
	for (auto& object : mObjects) {
		object->handleEvent(event);
	}
};

void Container::draw(sf::RenderWindow* target) {
	for (auto& object : mObjects) {
		object->draw(target);
	}
};