#pragma once

#include "GUI_Object.h"

#include "Container.h"

class DropDown : public GUI_Object
{
public:
	DropDown(sf::Texture* texture, RelativeRect rect);

	virtual bool update(sf::FloatRect parrentRect) override;
	virtual bool handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window) override;

	void setChild(std::unique_ptr<Container> child);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite mSprite;

	std::unique_ptr<Container> mChild;

	bool focus;
};

