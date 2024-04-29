#include "Game.hpp"
#include "Utility.hpp"
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <iostream>

Game::Game()
: running(false), window(nullptr), renderer(nullptr) {
    init();
}

Game::~Game() {
    clean();
}

void Game::loadLevel(const std::string& filename) {
    bricks.clear();

    std::ifstream file("levels/" + filename);
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << filename << std::endl;
        return;
    }
    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        int x = 0;
        for (char c : line) {
            if (c == '1') {
                bricks.emplace_back(x * 80, y * 40, 80, 40);
            }
            x++;
        }
        y++;
    }
    file.close();
}

void Game::loadLevels() {
    std::vector<Button> levelButtons;
    int buttonX = 10;
    int buttonY = 10;

    // Scan the level directory
    //list of files 
    std::vector<std::filesystem::directory_entry> files;
    for (const auto& entry : std::filesystem::directory_iterator("levels")) {
        if (entry.path().extension() == ".txt") {
            files.push_back(entry);
        }
    }
    //sort the files by name
    std::sort(files.begin(), files.end(), [](const auto& a, const auto& b) {
        return a.path().filename().string() < b.path().filename().string();
    });

    for (const auto& entry : files) {
        if (entry.path().extension() == ".txt") {
            // Extract level number from the filename
            std::string filename = entry.path().filename().string();
            std::string levelNumberStr = filename.substr(5, filename.size() - 9); // "levelX.txt"
            int levelNumber = std::stoi(levelNumberStr);

            // Create a button for this level
            // levelButtons.push_back(Button(buttonX, buttonY, "Level " + levelNumberStr));
            levelButtons.emplace_back(buttonX, buttonY, filename.substr(0, filename.size() - 4));

            // Update button position for the next button
            buttonY += 50;
        }
    }
    //on affiche les fichiers trouvé dans le dossier level dans le terminal
    for (const auto& entry : std::filesystem::directory_iterator("levels")) {
        if (entry.path().extension() == ".txt") {
            std::cout << entry.path().filename() << std::endl;
        }
    }
    // Main loop
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                printf("Mouse button down\n");
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                // Check if a level button was clicked
                for (const auto& button : levelButtons) {
                    if (button.isClicked(mouseX, mouseY)) {
                        // Extract level number from the button text
                        std::string buttonText = button.getText();
                        // Load the clicked level
                        running = false;
                        loadLevel(buttonText + ".txt");
                    }
                }
            }
        }

        // Render level buttons
        for (const auto& button : levelButtons) {
            button.render(renderer);
        }

        SDL_RenderPresent(renderer);
    }
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
    if (TTF_Init() == -1) {
    std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
    return;
}
    running = true;

    // Initialize game objects
    paddle.init(350, 550, 100, 20);
    ball.init(375, 300, 10);
    // On charge un fichier ASCII contenant la disposition des briques dans le dossier level
    //On affiche sur l'écran un bouton pour chaque fichier levelX.txt
    //On charge le fichier levelX.txt correspondant au bouton cliqué
    loadLevels();


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
    ball.checkCollisionPaddle(paddle.getRect());
    for (auto& brick : bricks) {
        if (ball.checkCollisionBrick(brick.getRect())) {
            brick.checkCollision(ball.getRect());
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
