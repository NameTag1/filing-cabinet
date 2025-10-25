#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

enum RelativeWH {
	Static,
	WBased,
	HBased,
	WHBased,
	Normal
}; //What the object's size scales on
enum Anchor {
	TL,
	TR,
	BL,
	BR,
	Center
}; //When the object grows/shrinks, what remains anchored

class RelativeRect
{
public:
	RelativeRect(sf::FloatRect rect);
	RelativeRect(sf::FloatRect rect, RelativeWH wh, Anchor a);
	void update(sf::FloatRect parentRect);
	void setRect(sf::FloatRect newRect);
	sf::FloatRect getRect();
	sf::FloatRect getRect(sf::FloatRect parentRect);
	void scaleSprite(sf::Sprite& sprite);
	void scaleSprite(sf::Sprite& sprite, bool maintainRatio);

private:
	//x, y, w, h all expressed as decimal (1-0) multiplied to 
	float x;
	float y;
	float w;
	float h;
	sf::FloatRect tempRect;
	RelativeWH mWH;
	Anchor mAnchor;
	sf::FloatRect i;
};

