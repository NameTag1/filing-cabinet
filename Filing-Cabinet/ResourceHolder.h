#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <map>

class ResourceHolder
{
public:
	ResourceHolder();
	static ResourceHolder* getInstance();
	sf::Texture* getTexture(std::string key);
	void loadTexture(const std::filesystem::path& filename, std::string key);

private:
	static ResourceHolder* instance;
	std::map<std::string, sf::Texture> mTextures;
};

