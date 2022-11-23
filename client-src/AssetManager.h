#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "SDL.h"
#include "SDL_mixer.h"

static class AssetManager {
private:
	static std::unordered_map<std::string, SDL_Texture*> textureMap;
	static std::unordered_map<std::string, Mix_Chunk*> soundMap;

public:

	static void addTexture(std::string key, SDL_Texture* texture);
	static SDL_Texture* getTexture(std::string key);

	static void addSound(std::string key, Mix_Chunk*);
	static Mix_Chunk* getSound(std::string key);

	static void cleanUp();
};