#pragma once

#include "GUI_Object.h"

#include "Container.h"

class Sidebar : public GUI_Object
{
public:
	Sidebar(sf::Texture* closedTexture, sf::Texture* openTexture, RelativeRect closedRect, RelativeRect openRect);

	virtual bool update(sf::FloatRect parrentRect) override;
	virtual bool handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window) override;

	void setChild(std::unique_ptr<Container> child);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite mClosedSprite;
	sf::Sprite mOpenSprite;

	RelativeRect mCloseRect;
	RelativeRect mOpenRect;

	std::unique_ptr<Container> mChild;
	
	bool mOpen;
	bool mOpenDelay;
};

