#pragma once
#include "SDL.h"
// On definit les 3 états possibles pour une brique
enum class BrickState {
    Green,
    Yellow,
    Red
};
class Brick {
public:
    Brick(int x, int y, int w, int h);
    void render(SDL_Renderer* renderer);
    bool checkCollision(const SDL_Rect& ball);
    SDL_Rect getRect() const;
    bool destroyed;
    BrickState state;


private:
    SDL_Rect rect;
};
