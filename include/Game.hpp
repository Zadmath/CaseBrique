#include <vector>
#include "SDL.h"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"
#include <string>
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
    void loadLevels();
    void loadLevel(const std::string& filename);
    SDL_Window* window;
    SDL_Renderer* renderer;
    Paddle paddle;
    Ball ball;
    std::vector
    <Brick> bricks;
};
