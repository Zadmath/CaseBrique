#include "Game.hpp"
#include <algorithm>

Game::Game()
: running(false), window(nullptr), renderer(nullptr) {
    init();
}

Game::~Game() {
    clean();
}

void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow("Casse-Brique",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800,
                              600,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return;
    }

    running = true;

    // Initialize game objects
    paddle.init(350, 550, 100, 20);
    ball.init(375, 300, 10);
    // Create some bricks
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            bricks.push_back(Brick(100 + i * 120, 50 + j * 35, 100, 30));
        }
    }
}

void Game::run() {
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        update();
        render();
    }
}

void Game::update() {
    // Update game objects
    paddle.update();
    ball.update();

    // Check collisions
    ball.checkCollision(paddle.getRect());
    for (auto& brick : bricks) {
        if (ball.checkCollision(brick.getRect())) {
            brick.destroyed = true;
        }
    }

    bricks.erase(std::remove_if(bricks.begin(), bricks.end(),
                                [](const Brick& b) { return b.destroyed; }),
                 bricks.end());
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render game objects
    paddle.render(renderer);
    ball.render(renderer);
    for (auto& brick : bricks) {
        brick.render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
