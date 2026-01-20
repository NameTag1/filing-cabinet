#include "FloatBox.h"

FloatBox::FloatBox(RelativeRect rect)
	: Container(rect)
	, mPadding(0.f)
{
}

void FloatBox::pushObject(std::unique_ptr<GUI_Object> object, FloatAlign align)
{
	object->setParrent(this);
	mItems.push_back({ std::move(object), align });
}

void FloatBox::setPadding(float padding)
{
	mPadding = padding;
}

bool FloatBox::update(sf::FloatRect parentRect)
{
	// Update own rect and transform (mirrors Container::update's initial steps).
	mRect.update(parentRect);
	setPosition(mRect.getRect().position);

	// Use our inner area as the parent rect for child RelativeRect calculations
	const sf::FloatRect inner = mRect.getRect();

	// Layout cursors (no wrapping; simple stacking per chosen float)
	float leftY = 0.f;
	float rightY = 0.f;
	float topX = 0.f;
	float bottomX = 0.f;

	for (auto& item : mItems) {
		// Let child compute its size relative to the FloatBox inner area.
		item.object->update(inner);

		const sf::FloatRect childRect = item.object->getRect();

		sf::Vector2f localPos(0.f, 0.f);

		switch (item.align) {
		case FloatAlign::Left:
			localPos.x = 0.f;
			localPos.y = leftY;
			leftY += childRect.size.y + mPadding;
			break;
		case FloatAlign::Right:
			localPos.x = inner.size.x - childRect.size.x;
			localPos.y = rightY;
			rightY += childRect.size.y + mPadding;
			break;
		case FloatAlign::Top:
			localPos.x = topX;
			localPos.y = 0.f;
			topX += childRect.size.x + mPadding;
			break;
		case FloatAlign::Bottom:
			localPos.x = bottomX;
			localPos.y = inner.size.y - childRect.size.y;
			bottomX += childRect.size.x + mPadding;
			break;
		}

		// FloatBox fully controls final x/y (width/height remain driven by RelativeRect)
		item.object->setPosition(localPos);
	}

	return false;
}

bool FloatBox::handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window)
{
	// Propagate events to children in insertion order. All objects are itterated through and return true if just one is true.
	// This is because events from this container very unlikely to be relavant to multiple items.
	bool stick = false;
	for (auto& item : mItems) {
		if (item.object->handleEvent(event, window)) {
			stick = true;
		}
	}
	return stick;
}

void FloatBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply this object's transform, then draw children positioned in local coords.
	states.transform *= getTransform();

	for (const auto& item : mItems) {
		target.draw(*item.object, states);
	}
}
