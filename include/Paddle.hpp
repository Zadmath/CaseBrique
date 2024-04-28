#pragma once
#include "SDL.h"

class Paddle {
public:
    Paddle();
    void init(int x, int y, int w, int h);
    void update();
    void render(SDL_Renderer* renderer);
    SDL_Rect getRect() const;

private:
    SDL_Rect rect;
    int speed;
};
