#pragma once
#include <SDL.h>
const float maxSpeed = 1.0f;
class Ball {
public:
    Ball();
    void init(float x, float y, int radius, float speedX = maxSpeed*sin(0), float speedY = maxSpeed*cos(0));
    void update();
    void render(SDL_Renderer* renderer);
    bool checkCollisionBrick(const SDL_Rect& brick);
    bool checkCollisionPaddle(const SDL_Rect& paddle);
    SDL_Rect getRect();

private:
    SDL_Rect rect;
    float x_pos, y_pos;
    float speedX, speedY;
};
