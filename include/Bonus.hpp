// Bonus.hpp
#ifndef BONUS_HPP
#define BONUS_HPP

#include "Paddle.hpp"
#include "Game.hpp"

enum class BonusType {
    PaddleSizeIncrease,
    SpeedBoost,
    ExtraBall
};

class Bonus {
public:
    Bonus(BonusType type);
    void spawn(int x, int y, int w, int h);
    void update();
    void render(SDL_Renderer* renderer);
    bool checkCollision(const SDL_Rect& paddleRect);
    bool isActive() const;
    void activate(Paddle& paddle, Game& game);
    void deactivate();
private:
    BonusType type;
    SDL_Rect rect;
    bool active;
};

#endif // BONUS_HPP
