#pragma once

#include "GUI_Object.h"

#include "Container.h"

class ScrollBox : public GUI_Object
{
public:
	ScrollBox(sf::Texture* texture, RelativeRect rect);

	virtual bool update(sf::FloatRect parrentRect) override;
	virtual bool handleEvent(const std::optional<sf::Event> event, sf::RenderWindow* window) override;

	void setChild(std::unique_ptr<Container> child);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	float scroll; //How much the user has scrolled
	//RelativeRect mInternalRect; //Used to calculate position of inside

	sf::Sprite mBar; //Bar in back showing how far you can scroll
	sf::Sprite mTracker; //Where you are scrollwise

	std::unique_ptr<Container> mChild;

	bool focus;
};

