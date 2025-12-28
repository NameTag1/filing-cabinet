#include "ChangeableBox.h"

#include "Logger.h"

ChangeableBox::ChangeableBox(RelativeRect Rect)
	: GUI_Object(Rect)
	, held(false)
{
}

bool ChangeableBox::update(sf::FloatRect parrentRect)
{
	mRect.update(parrentRect);
	return false;
}

bool ChangeableBox::handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window)
{
	if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
		if (mouseEvent->button == sf::Mouse::Button::Left)
		{
			// Convert window pixel coords -> world coords
			sf::Vector2f mouseWorld = window->mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

			// Convert world coords into this object's local coords
			sf::Vector2f localPos = getInverseTransform().transformPoint(mouseWorld);

			// Local rect is (0,0) .. (width, height)
			const sf::FloatRect rectLocal({ 0.f, 0.f }, { mRect.getRect().size.x, mRect.getRect().size.y });

			if (rectLocal.contains(localPos)) {
				held = true;
				return true;
			}
		}
	}
	if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonReleased>()) {
		if ((mouseEvent->button == sf::Mouse::Button::Left) && held)
		{
			// Convert window pixel coords -> world coords
			sf::Vector2f mouseWorld = window->mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

			// Convert world coords into this object's local coords
			sf::Vector2f localPos = getInverseTransform().transformPoint(mouseWorld);

			// Local rect is (0,0) .. (width, height)
			const sf::FloatRect rectLocal({ 0.f, 0.f }, { mRect.getRect().size.x, mRect.getRect().size.y });

			if (rectLocal.contains(localPos)) {
				held = true;
				return true;
			}
		}
	}
	if (const auto* mouseEvent = event->getIf<sf::Event::MouseMoved>()) {
		if (held)
		{
			// Convert window pixel coords -> world coords
			sf::Vector2f mouseWorld = window->mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

			// Convert world coords into this object's local coords
			sf::Vector2f localPos = getInverseTransform().transformPoint(mouseWorld);

			// Local rect is (0,0) .. (width, height)
			const sf::FloatRect rectLocal({ 0.f, 0.f }, { mRect.getRect().size.x, mRect.getRect().size.y });

			if (rectLocal.contains(localPos)) {
				held = true;
				return true;
			}
		}
	}
	return false;
}

void ChangeableBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*mChild, states);
}

void ChangeableBox::setChild(std::unique_ptr<Container> child)
{
	mChild = std::move(child);
}

