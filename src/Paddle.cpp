#include "Paddle.hpp"

Paddle::Paddle() : rect{0, 0, 100, 20}, speed(4) {
}

void Paddle::init(int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Paddle::update() {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    int x, y;
    SDL_GetMouseState(&x, &y);
    //control with mouse
    if (x>rect.w/2 && x<800-rect.w/2) {


        
        rect.x = x - rect.w / 2;
        if (rect.x < 0) {
            rect.x = 0;
        }
        if (rect.x > 800 - rect.w) {
            rect.x = 800 - rect.w;
        }
    }
    //control avec les fleches si la souris n'est pas utilisée

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
