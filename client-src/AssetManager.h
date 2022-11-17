#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "SDL.h"

class AssetManager {
private:
	std::unordered_map<std::string, SDL_Texture*> textureMap;

public:
	AssetManager();

	void addTexture(std::string key, SDL_Texture* texture);
	SDL_Texture* getTexture(std::string key);
};