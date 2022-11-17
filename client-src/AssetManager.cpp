#include "AssetManager.h"

void AssetManager::addTexture(std::string key, SDL_Texture* texture) {
	textureMap.insert({ key, texture });
}

SDL_Texture* AssetManager::getTexture(std::string key) {
	return textureMap.at(key);
}