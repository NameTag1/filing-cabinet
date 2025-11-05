#include "Container.h"

Container::Container(RelativeRect rect)
	: mRect(rect)
{
}

void Container::pushObject(std::unique_ptr<GUI_Object> object)
{
	mObjects.push_back(std::move(object));
}

void Container::update(sf::FloatRect parentRect) {
	mRect.update(parentRect); //Update own rect based on parrent rect BEFORE updating children
	sf::FloatRect currentRect = mRect.getRect();
	for(auto& object : mObjects) {
		object->update(currentRect);
	}
};

void Container::handleEvent(const std::optional<sf::Event> event) {
	for (auto& object : mObjects) {
		object->handleEvent(event);
	}
};

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& object : mObjects) {
		target.draw(*object.get(), states);
	}
};