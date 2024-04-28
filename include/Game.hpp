#include <vector>
#include "SDL.h"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void init();
    void update();
    void render();
    void clean();
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Paddle paddle;
    Ball ball;
    std::vector
    <Brick> bricks;
};
