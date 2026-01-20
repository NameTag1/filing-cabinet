#pragma once

#include "Container.h"
#include <vector>
#include <memory>

enum FloatAlign {
	Left,
	Right,
	Top,
	Bottom
};

class FloatBox : public Container
{
public:
	FloatBox(RelativeRect rect);

	// Add a child with a float alignment. Default is Left.
	void pushObject(std::unique_ptr<GUI_Object> object, FloatAlign align = FloatAlign::Left);

	// Padding (in local pixels) placed between floats when laying out children.
	void setPadding(float padding);

	virtual bool update(sf::FloatRect parentRect) override;
	virtual bool handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window) override;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	struct Item {
		std::unique_ptr<GUI_Object> object;
		FloatAlign align;
	};

	std::vector<Item> mItems;
	float mPadding;
};

