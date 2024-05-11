#include "Bonus.hpp"

Bonus::Bonus(BonusType type) : type(type), active(false) {}

void Bonus::spawn(int x, int y, int w, int h) {
    // Set the position and size of the bonus
    // Randomize the position if needed
    // Activate the bonus
}

void Bonus::update() {
    // Update the bonus's position or other properties if needed
}

void Bonus::render(SDL_Renderer* renderer) {
    // Render the bonus on the screen if active
}

bool Bonus::checkCollision(const SDL_Rect& paddleRect) {
    // Check for collision with the paddle
    // If collision detected, return true
    // Otherwise, return false
}

bool Bonus::isActive() const {
    return active;
}

void Bonus::activate(Paddle& paddle, Game& game) {
    switch (type) {
        case BonusType::PaddleSizeIncrease:
            paddle.increaseSize();
            break;
        case BonusType::SpeedBoost:
            paddle.increaseSpeed();
            break;
        case BonusType::ExtraBall:
            game.addBall();
            break;
        default:
            break;
    }
    active = true;
}

void Bonus::deactivate() {
    // Deactivate the bonus
    active = false;
}
