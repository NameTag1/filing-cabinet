#pragma once

#include "GUI_Object.h"
#include "Container.h"
#include <SFML/Window/Cursor.hpp>

class ExpandableSidebar : public GUI_Object
{
public:
	enum class Edge {
		Left,
		Right
	};

	ExpandableSidebar(sf::Texture* texture, RelativeRect rect, Edge edge = Edge::Left, float minWidthPx = 50.f);

	virtual bool update(sf::FloatRect parrentRect) override;
	virtual bool handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window) override;

	void setChild(std::unique_ptr<Container> child);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite mSprite;
	std::unique_ptr<Container> mChild;

	Edge mEdge;

	// Dragging state
	bool mDragging;
	float mHandleThicknessPx; // hit area thickness in pixels
	float mMinWidthPx;

	// Cursor handling
	sf::Cursor mHandCursor;
	sf::Cursor mArrowCursor;
	bool mHandCursorLoaded;
	bool mArrowCursorLoaded;
	bool mCursorSetToHand;
};

