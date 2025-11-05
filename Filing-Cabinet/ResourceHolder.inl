#include "Logger.h"

template <typename T>
T* ResourceHolder<T>::getResource(std::string key)
{
	//If texture not found, return nullptr
	if (mResources.find(key) == mResources.end()) {
		Logger::Instance->LogData(Logger::Sys, "Texture with key '" + key + "' not found!");
		return nullptr;
	}
	return &mResources[key];
}

template <typename T>
void ResourceHolder<T>::loadResource(const std::filesystem::path& filename, std::string key)
{
	if (mResources.find(key) != mResources.end()) {
		return; //File already loaded, just exit
	}
	T resource;
	if (!resource.loadFromFile(filename)) {
		Logger::Instance->LogData(Logger::Sys, "Failed to load texture from file: " + filename.string());
		return;
	}
	mResources[key] = resource;

	Logger::Instance->LogData(Logger::Action, "Loaded texture from file: " + filename.string() + " with key: " + key);
}