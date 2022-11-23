#include "Entity.h"

Entity::Entity(int x, int y, int w, int h) {
    rect = { x, y, w, h };
}

void Entity::setPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void Entity::renderEntity(SDL_Renderer* renderer, SDL_Texture* texture) {

    // COLLISION DEBUGGING

    /*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &player1);
    SDL_RenderDrawRect(renderer, &player2);
    SDL_RenderDrawRect(renderer, &ball);*/

    SDL_RenderCopy(renderer, texture, NULL, &rect);
}