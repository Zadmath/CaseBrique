#include "Ball.hpp"
#include <iostream>
#include <ctime>
Ball::Ball() : rect{0, 0, 20, 20}, speedX(5), speedY(5) {
}

void Ball::init(float x, float y, int radius, float speedX, float speedY) {
    this->rect.x = x;
    x_pos = x;
    this->rect.y = y;
    y_pos = y;
    this->rect.w = radius * 2;
    this->rect.h = radius * 2;
    this->speedX = speedX;
    this->speedY = speedY;
}

void Ball::update() {
    x_pos += speedX;
    y_pos += speedY;
    rect.x = x_pos;
    rect.y = y_pos;
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

bool Ball::checkCollisionBrick(const SDL_Rect& brick) {
    if (rect.x < brick.x + brick.w &&
        rect.x + rect.w > brick.x &&
        rect.y < brick.y + brick.h &&
        rect.y + rect.h > brick.y) {
        
        // On calcule la direction de la balle après la collision
        // On calcule le centre de la balle et de la brique
        float ballCenterX = rect.x + rect.w / 2.0f;
        float ballCenterY = rect.y + rect.h / 2.0f;
        float brickCenterX = brick.x + brick.w / 2.0f;
        float brickCenterY = brick.y + brick.h / 2.0f;

        float diffX = ballCenterX - brickCenterX;
        float diffY = ballCenterY - brickCenterY;

        // On normalise le vecteur de différence
        float magnitude = sqrt(diffX * diffX + diffY * diffY);
        diffX /= magnitude;
        diffY /= magnitude;

        // Si la balle touche le coin de la brique, on inverse les deux directions
        // Sinon, on inverse seulement la direction de la balle
        
        if (std::abs(diffX) > std::abs(diffY)) {
            speedX = -speedX;
        } else {
            speedY = -speedY;
        }

        return true;
    }

    return false;
}

bool Ball::checkCollisionPaddle(const SDL_Rect& paddle) {
    if (rect.x < paddle.x + paddle.w &&
        rect.x + rect.w > paddle.x &&
        rect.y < paddle.y + paddle.h &&
        rect.y + rect.h > paddle.y) {
        // On calcule la direction de la balle après la collision
        float paddleCenter = paddle.x + paddle.w / 2.0f;
        float ballCenter = rect.x + rect.w / 2.0f;
        float distanceFromCenter = (ballCenter - paddleCenter) / (paddle.w / 2.0f);

        // On calcule l'angle de rebond de la balle
        float minAngle = M_PI / 4;  // 45 degrees
        float maxAngle = 3 * M_PI / 4;  // 135 degrees
        float angle = (distanceFromCenter * (maxAngle - minAngle) + (maxAngle + minAngle)) / 2;

        // Update speedX and speedY based on the new angle
        speedX = -maxSpeed * cos(angle);
        speedY = -maxSpeed * sin(angle);  
        return true;
    }

    return false;
}

SDL_Rect Ball::getRect() {
    return rect;
}
