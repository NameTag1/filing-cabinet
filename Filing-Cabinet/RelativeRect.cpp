#include "RelativeRect.h"
#include <iostream>

RelativeRect::RelativeRect(sf::FloatRect rect)
: x(rect.position.x)
, y(rect.position.y)
, w(rect.size.x)
, h(rect.size.y)
, mWH(Normal)
, mAnchor(TL)
{
	
}

RelativeRect::RelativeRect(sf::FloatRect rect, RelativeWH wh, Anchor a)
: x(rect.position.x)
, y(rect.position.y)
, w(rect.size.x)
, h(rect.size.y)
, mWH(wh)
, mAnchor(a)
{
}

//Adjusts absolute rect according to parent rect
void RelativeRect::update(sf::FloatRect parentRect)
{
	if (mWH == RelativeWH::Static) {
		tempRect.size.x = w;
		tempRect.size.y = h;
	}

	if (mWH == RelativeWH::WBased) {
		tempRect.size.x = parentRect.size.x * w;
		tempRect.size.y = tempRect.size.x / w * h;
	}

	if (mWH == RelativeWH::HBased) {
		tempRect.size.y = parentRect.size.y * h;
		tempRect.size.x = tempRect.size.y / h * w;
	}

	if (mWH == RelativeWH::WHBased) {
		if (parentRect.size.x * w > parentRect.size.y * h) {
			tempRect.size.x = parentRect.size.x * w;
			tempRect.size.y = tempRect.size.x / w * h;
		}
		else {
			tempRect.size.y = parentRect.size.y * h;
			tempRect.size.x = tempRect.size.y / h * w;
		}
	}

	if (mWH == RelativeWH::Normal) {
		tempRect.size.x = parentRect.size.x * w;
		tempRect.size.y = parentRect.size.y * h;
	}

	tempRect.position.x = 0;//(parentRect.size.x) - (tempRect.size.x / 2);
	tempRect.position.y = 0; //(parentRect.size.y) - (tempRect.size.y / 2);


	if (mAnchor == Anchor::TL) {
		tempRect.position.x = parentRect.size.x * x;
		tempRect.position.y = parentRect.size.y * y;
	}

	if (mAnchor == Anchor::TR) {
		tempRect.position.x = parentRect.size.x * x - tempRect.size.x;
		tempRect.position.y = parentRect.size.y * y;
	}
	
	if (mAnchor == Anchor::BL) {
		tempRect.position.x = parentRect.size.x * x;
		tempRect.position.y = parentRect.size.y * y - tempRect.size.y;
	}

	if (mAnchor == Anchor::BR) {
		tempRect.position.x = parentRect.size.x * x - tempRect.size.x;
		tempRect.position.y = parentRect.size.y * y - tempRect.size.y;
	}

	if (mAnchor == Anchor::Center) {
		tempRect.position.x = parentRect.size.x * x - tempRect.size.x/2;
		tempRect.position.y = parentRect.size.y * y - tempRect.size.y/2;
	}

	//std::cout << tempRect.position.x << "\n";
}

//Sets new relative rect 
void RelativeRect::setRect(sf::FloatRect newRect)
{
	x = newRect.position.x;
	y = newRect.position.y;
	w = newRect.size.x;
	h = newRect.size.y;
}

sf::FloatRect RelativeRect::getRect()
{
	return tempRect;
}

sf::FloatRect RelativeRect::getRect(sf::FloatRect target)
{
	update(target);
	return tempRect;
}

//Set sprite dimentions to rect
void RelativeRect::scaleSprite(sf::Sprite& sprite)
{
	const sf::FloatRect local = sprite.getLocalBounds();
	if (local.size.x <= 0.f || local.size.y <= 0.f) return;
	sprite.setScale({ tempRect.size.x / local.size.x, tempRect.size.y / local.size.y });
}

//Set sprite dimentions to rect, with option to maintain ratio
void RelativeRect::scaleSprite(sf::Sprite& sprite, bool maintainRatio)
{
	float scalex = tempRect.size.x / sprite.getGlobalBounds().size.x;
	float scaley = tempRect.size.y / sprite.getGlobalBounds().size.y;

	if (mWH == RelativeWH::WBased) {
		scalex = tempRect.size.x / sprite.getGlobalBounds().size.x;
		scaley = scalex;
	}

	if (mWH == RelativeWH::HBased) {
		scaley = tempRect.size.y / sprite.getGlobalBounds().size.y;
		scalex = scaley;
	}

	if (mWH == RelativeWH::WHBased) {
		if (tempRect.size.x * w > tempRect.size.y * h) {
			scalex = tempRect.size.x / sprite.getGlobalBounds().size.x;
			scaley = scalex;
		}
		else {
			scaley = tempRect.size.y / sprite.getGlobalBounds().size.y;
			scalex = scaley;
		}
	}

	sprite.scale({ scalex, scaley });
}


