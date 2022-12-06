#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "Vector2.h"
#include "SDL_ttf.h"


class Text
{

    public:
        SDL_Texture* createTextureFromString(SDL_Renderer* renderer, std::string text, SDL_Color color, TTF_Font* font);
        Vector2 positionText(Vector2 initPosition, int textW, int textH);
        void renderText(SDL_Renderer* renderer, int xPos, int yPos, std::string text, SDL_Color color, TTF_Font* font);
};

