#include "Entity.h"

Entity::Entity(int x, int y, int w, int h) {
    rect = { x, y, w, h };
}

void Entity::setPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void Entity::renderEntity(SDL_Renderer* renderer, SDL_Texture* texture) {

    SDL_RenderCopy(renderer, texture, NULL, &rect);
}