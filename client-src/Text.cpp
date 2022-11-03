#include "Text.h"

void Text::init() {
    font = TTF_OpenFont("fonts/OpenSans.ttf", 32);
    if (!font) {
        printf("TTF_INIT: %s\n", TTF_GetError());
        exit(0);
    }
}

void Text::renderText(SDL_Renderer* renderer, int xPos, int yPos, std::string text, SDL_Color color) {

    SDL_Texture* texture = createTextureFromString(renderer, text, color);

    // get size of text texture
    int textW;
    int textH;
    SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);

    // position text
    vector2 initPosition;
    initPosition.x = xPos;
    initPosition.y = yPos;
    vector2 position = positionText(initPosition, textW, textH);

    // render text
    SDL_Rect textureRect = { position.x, position.y, textW, textH };
    SDL_RenderCopy(renderer, texture, NULL, &textureRect);

    SDL_DestroyTexture(texture);
}

vector2 Text::positionText(vector2 initPosition, int textW, int textH) {
    vector2 position = initPosition;

    position.x -= textW / 2;
    position.y -= textH / 2;

    return position;
}

SDL_Texture* Text::createTextureFromString(SDL_Renderer* renderer, std::string text, SDL_Color color) {

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return texture;
}