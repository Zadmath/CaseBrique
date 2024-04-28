#include <SDL.h>
#include <vector>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <SDL_ttf.h>
// Assuming you have a Button class that handles rendering and click detection
class Button {
private:
    SDL_Rect rect;
    std::string text;
    TTF_Font* font;
public:
    Button(int x, int y, const std::string& text);
    void render(SDL_Renderer* renderer) const;
    bool isClicked(int mouseX, int mouseY) const;
    std::string getText() const;
};

