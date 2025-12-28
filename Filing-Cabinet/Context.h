#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "Logger.h"
#include "ResourceHolder.h"

struct Context {
	sf::RenderWindow* mWindow;
	TextureHolder* mTextureHolder;
	FontHolder* mFontHolder;
};