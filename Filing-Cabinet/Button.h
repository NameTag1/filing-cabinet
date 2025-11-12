#pragma once

#include "GUI_Object.h"
#include <functional>

class Button : public GUI_Object
{
public:
	Button(sf::Texture* texture, RelativeRect rect);

	void SetCallback(std::function<void()> callback);

	virtual bool update(sf::FloatRect parrentRect) override;
	virtual bool handleEvent(const std::optional<sf::Event> event) override;

	virtual void activate() override;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::function<void()> mCallback;
	sf::Sprite mSprite;
};
