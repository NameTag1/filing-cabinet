#pragma once

#include "GUI_Object.h"
#include <functional>

class Button : public GUI_Object
{
public:
	Button(sf::Texture* texture, sf::Texture* hoverTexture, RelativeRect rect);

	void SetCallback(std::function<void()> callback);

	virtual bool update(sf::FloatRect parrentRect) override;
	virtual bool handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window) override;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool hoveredOver;
	std::function<void()> mCallback;
	sf::Sprite mSprite;
	sf::Sprite mHoverSprite;
};
