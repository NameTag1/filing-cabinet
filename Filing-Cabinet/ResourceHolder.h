#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <map>
#include <filesystem>

template <typename T> 
class ResourceHolder
{
public:
	T* getResource(const std::string& key);
	void loadResource(const std::filesystem::path& filename, const std::string& key);

private:
	std::map<std::string, T> mResources;
};

#include "ResourceHolder.inl"

typedef ResourceHolder<sf::Texture> TextureHolder;
typedef ResourceHolder<sf::Font> FontHolder;