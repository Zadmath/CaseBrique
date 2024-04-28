#include "Ball.hpp"

Ball::Ball() : rect{0, 0, 20, 20}, speedX(5), speedY(5) {
}

void Ball::init(int x, int y, int radius, int speedX, int speedY) {
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = radius * 2;
    this->rect.h = radius * 2;
    this->speedX = speedX;
    this->speedY = speedY;
}

void Ball::update() {
    rect.x += speedX;
    rect.y += speedY;

    // Collision avec les bords de la fenêtre
    if (rect.x <= 0 || rect.x + rect.w >= 800) {
        speedX = -speedX;  // Inverse la direction horizontale
    }
    if (rect.y <= 0 || rect.y + rect.h >= 600) {
        speedY = -speedY;  // Inverse la direction verticale
    }
}

void Ball::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanc
    SDL_RenderFillRect(renderer, &rect);
}

bool Ball::checkCollision(const SDL_Rect& paddle) {
    // Collision simple AABB avec le paddle
    if (rect.x < paddle.x + paddle.w &&
        rect.x + rect.w > paddle.x &&
        rect.y < paddle.y + paddle.h &&
        rect.y + rect.h > paddle.y) {
        speedY = -speedY;  // Inverse la direction verticale après collision
        return true;

    }
    return false;
}

SDL_Rect Ball::getRect() {
    return rect;
}
