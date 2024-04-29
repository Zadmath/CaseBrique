#include "Brick.hpp"

Brick::Brick(int x, int y, int w, int h)
: destroyed(false) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    state = BrickState::Green;
}

void Brick::render(SDL_Renderer* renderer) {
    if (!destroyed) {
        switch (state) {
            case BrickState::Green:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
                break;
            case BrickState::Yellow:
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
                break;
            case BrickState::Red:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
                break;
        }
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
        
        if(state == BrickState::Green && !destroyed) { // Check if the brick is not already destroyed
            state = BrickState::Yellow;
        } else if(state == BrickState::Yellow && !destroyed) { // Check if the brick is not already destroyed
            state = BrickState::Red;
        } else {
            destroyed = true;
        }
        return true;
    }
    return false;
}

SDL_Rect Brick::getRect() const {
    return rect;
}