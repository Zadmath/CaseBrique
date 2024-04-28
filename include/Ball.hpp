#pragma once
#include <SDL.h>

class Ball {
public:
    Ball();
    void init(int x, int y, int radius, int speedX = 5, int speedY = 5);
    void update();
    void render(SDL_Renderer* renderer);
    bool checkCollision(const SDL_Rect& paddle);
    SDL_Rect getRect();

private:
    SDL_Rect rect;
    int speedX, speedY;
};
