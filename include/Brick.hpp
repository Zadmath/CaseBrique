#pragma once
#include "SDL.h"

class Brick {
public:
    Brick(int x, int y, int w, int h);
    void render(SDL_Renderer* renderer);
    bool checkCollision(const SDL_Rect& ball);
    SDL_Rect getRect() const;
    bool destroyed;

private:
    SDL_Rect rect;
};
