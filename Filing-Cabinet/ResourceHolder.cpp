#include "ResourceHolder.h"

#include "Logger.h"

ResourceHolder* ResourceHolder::instance = new ResourceHolder();

ResourceHolder::ResourceHolder()
{

}

ResourceHolder* ResourceHolder::getInstance()
{
	return instance;
}

sf::Texture* ResourceHolder::getTexture(std::string key)
{
	//If texture not found, return nullptr
    if(mTextures.find(key) == mTextures.end()) {
		Logger::Instance->LogData(Logger::Sys, "Texture with key '" + key + "' not found!");
        return nullptr;
	}
    return &mTextures[key];
}

void ResourceHolder::loadTexture(const std::filesystem::path& filename, std::string key)
{
	if (mTextures.find(key) != mTextures.end()) {
		return; //File already loaded, just exit
	}
	sf::Texture texture;
	if (!texture.loadFromFile(filename)) {
		Logger::Instance->LogData(Logger::Sys, "Failed to load texture from file: " + filename.string());
		return;
	}
	mTextures[key] = texture;

	Logger::Instance->LogData(Logger::Action, "Loaded texture from file: " + filename.string() + " with key: " + key);
}
