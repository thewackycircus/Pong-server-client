#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"

#include "Vector2.h"


class Entity
{
    private:
        SDL_Rect rect;

    public:

        // constructors
        Entity();

        Entity(int x, int y, int w, int h);

        // getter
        void setPosition(int x, int y);

        // functions
        SDL_Texture* createTextureFromImg(SDL_Renderer* renderer, std::string img);
        void renderEntity(SDL_Renderer* renderer, SDL_Texture* texture);
};