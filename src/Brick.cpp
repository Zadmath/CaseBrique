#include "Brick.hpp"

Brick::Brick(int x, int y, int w, int h)
: destroyed(false) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Brick::render(SDL_Renderer* renderer) {
    if (!destroyed) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
        SDL_RenderFillRect(renderer, &rect);
    }
}

bool Brick::checkCollision(const SDL_Rect& ball) {
    // Vérification simple de collision AABB (Axis-Aligned Bounding Box)
    if (!destroyed &&
        ball.x + ball.w > rect.x &&
        ball.x < rect.x + rect.w &&
        ball.y + ball.h > rect.y &&
        ball.y < rect.y + rect.h) {
        destroyed = true; // La brique est détruite lors de la collision
        return true;
    }
    return false;
}

SDL_Rect Brick::getRect() const {
    return rect;
}