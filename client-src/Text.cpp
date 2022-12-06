#include "Text.h"

void Text::renderText(SDL_Renderer* renderer, int xPos, int yPos, std::string text, SDL_Color color, TTF_Font* font) {

    SDL_Texture* texture = createTextureFromString(renderer, text, color, font);

    // get size of text texture
    int textW;
    int textH;
    SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);

    // position text
    Vector2 initPosition = Vector2(xPos, yPos);
    Vector2 position = positionText(initPosition, textW, textH);

    // render text
    SDL_Rect textureRect = { position.getX(), position.getY(), textW, textH};
    SDL_RenderCopy(renderer, texture, NULL, &textureRect);

    SDL_DestroyTexture(texture);
}

Vector2 Text::positionText(Vector2 initPosition, int textW, int textH) {
    Vector2 position = initPosition;

    int newXPos = position.getX() - textW / 2;
    int newYPos = position.getY() - textH / 2;

    position.setX(newXPos);
    position.setY(newYPos);

    return position;
}

SDL_Texture* Text::createTextureFromString(SDL_Renderer* renderer, std::string text, SDL_Color color, TTF_Font* font) {

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return texture;
}