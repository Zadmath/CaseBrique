#include "Paddle.hpp"

Paddle::Paddle() : rect{0, 0, 100, 20}, speed(10) {
}

void Paddle::init(int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Paddle::update() {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_LEFT]) {
        rect.x -= speed;
        if (rect.x < 0) {
            rect.x = 0;
        }
    }
    if (keystates[SDL_SCANCODE_RIGHT]) {
        rect.x += speed;
        if (rect.x > 800 - rect.w) {
            rect.x = 800 - rect.w;
        }
    }
}

void Paddle::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect Paddle::getRect() const {
    return rect;
}
