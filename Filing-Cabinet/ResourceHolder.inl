#include "Logger.h"
#include <type_traits>

template <typename T>
T* ResourceHolder<T>::getResource(const std::string& key)
{
	auto it = mResources.find(key);
	if (it == mResources.end()) {
		Logger::Instance->LogData(Logger::Sys, "Resource with key '" + key + "' not found!");
		return nullptr;
	}
	return &it->second;
}

template <typename T>
void ResourceHolder<T>::loadResource(const std::filesystem::path& filename, const std::string& key)
{
	if (mResources.find(key) != mResources.end()) {
		return; // File already loaded
	}

	T resource;
	bool loaded = false;

	// Use compile-time dispatch to call the correct load function for sf::Font vs other SFML resources.
	if constexpr (std::is_same_v<T, sf::Font>) {
		// Some SFML-like font implementations expose openFromFile instead of loadFromFile
		loaded = resource.openFromFile(filename.string());
	} else {
		loaded = resource.loadFromFile(filename.string());
	}

	if (!loaded) {
		Logger::Instance->LogData(Logger::Sys, "Failed to load resource from file: " + filename.string());
		return;
	}

	mResources.emplace(key, std::move(resource));
}