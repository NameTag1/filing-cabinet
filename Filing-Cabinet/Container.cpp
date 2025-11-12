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
	setPosition(mRect.getRect().position);

	sf::FloatRect currentRect = mRect.getRect();
	for(auto& object : mObjects) {
		if (object->update(currentRect)) {
			break;
		};
	}
};

void Container::handleEvent(const std::optional<sf::Event> event) {
	for (auto& object : mObjects) {
		if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonReleased>()) {
			if (mouseEvent->button == sf::Mouse::Button::Left)
			{
				if (object->getRect().contains(sf::Vector2f(mouseEvent->position))) {
					object->activate();
				}
			}
		}
	}
};

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	for (auto& object : mObjects) {
		target.draw(*object, states);
	}
};