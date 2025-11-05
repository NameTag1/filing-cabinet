#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "Logger.h"
#include "ResourceHolder.h"

struct Context {
	sf::RenderWindow* mWindow;
	Logger* mLogger;
	TextureHolder* mTextureHolder;
	FontHolder* mFontHolder;
};