#include "AssetManager.h"

std::unordered_map<std::string, SDL_Texture*> AssetManager::textureMap;
std::unordered_map<std::string, Mix_Chunk*> AssetManager::soundMap;
std::unordered_map<std::string, TTF_Font*> AssetManager::fontMap;

void AssetManager::addTexture(std::string key, SDL_Texture* texture) {
	textureMap.insert({ key, texture });
}

SDL_Texture* AssetManager::getTexture(std::string key) {
	return textureMap.at(key);
}

void AssetManager::addSound(std::string key, Mix_Chunk* sound) {
	soundMap.insert({ key, sound });
}

Mix_Chunk* AssetManager::getSound(std::string key) {
	return soundMap.at(key);
}

void AssetManager::addFont(std::string key, TTF_Font* font) {
	fontMap.insert({ key, font });
}

TTF_Font* AssetManager::getFont(std::string key) {
	return fontMap.at(key);
}

void AssetManager::cleanUp() {
	for (auto& pair : textureMap)
	{
		SDL_DestroyTexture(pair.second);
	}

	for (auto& pair : soundMap) 
	{
		Mix_FreeChunk(pair.second);
	}

	for (auto& pair : fontMap) 
	{
		TTF_CloseFont(pair.second);
	}
}