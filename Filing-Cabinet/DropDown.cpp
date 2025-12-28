#include "DropDown.h"

#include "Logger.h"
#include "Sidebar.h"

DropDown::DropDown(sf::Texture* texture, RelativeRect rect) 
	: mSprite(*texture)
	, focus(false)
	, GUI_Object(rect)
{

}

bool DropDown::update(sf::FloatRect parrentRect)
{
	mRect.update(parrentRect);
	mRect.scaleSprite(mSprite);
	setPosition(mRect.getRect().position);

	mChild->update(parrentRect); //Updated off of parrent rect (mRect just for button display)

	return false;
}

bool DropDown::handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window)
{
	if (!event.has_value() || window == nullptr) return false;

	if (focus) {
		if (mChild->handleEvent(event, window)) {
			//If child is being hovered over, focus maintained
			focus = true;
			return true;
		}
	}

	if (const auto* mouseEvent = event->getIf<sf::Event::MouseMoved>()) {
		// Convert window pixel coords -> world coords
		sf::Vector2f mouseWorld = window->mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

		// Convert world coords into this object's local coords
		sf::Vector2f localPos = getInverseTransform().transformPoint(mouseWorld);

		// Local rect is (0,0) .. (width, height)
		const sf::FloatRect rectLocal({ 0.f, 0.f }, { mRect.getRect().size.x, mRect.getRect().size.y });

		if (rectLocal.contains(localPos)) {
			focus = true;
			return true;
		}
		else {
			focus = false;
		}
	}

	//Run twice for safety
	if (focus) {
		if (mChild->handleEvent(event, window)) {
			//If child is being hovered over, focus maintained
			focus = true;
			return true;
		}
	}

	return false;
}

void DropDown::setChild(std::unique_ptr<Container> child)
{
	mChild = std::move(child);
}

void DropDown::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
	//Draw Children FIRST because otherwise is transformed by parrent dimentions
	if (focus == true) {
		target.draw(*mChild, states);
	}

	states.transform *= getTransform();
	target.draw(mSprite, states);
}
