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
#include "Utility.hpp"

 
Button::Button(int x, int y, const std::string& text) {
    rect.x = x;
    rect.y = y;
    rect.w = 200;
    rect.h = 50;

    this->text = text;
    font = TTF_OpenFont("font/Arial.ttf", 24);

}

void Button::render(SDL_Renderer* renderer) const{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color { 255, 255, 255 });

    //surface->w provoque un segfault car surface est NULL il faut donc utiliser surface->w et surface->h
    if (!surface) {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
    return;
}
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect textRect = { rect.x + rect.w / 2 - surface->w / 2, rect.y + rect.h / 2 - surface->h / 2, surface->w, surface->h };
        
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

bool Button::isClicked(int mouseX, int mouseY) const{
    return mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h;
}

std::string Button::getText() const{
    return text;
}

// Assuming you have a function that loads a font
TTF_Font* loadFont(const std::string& path, int size) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    return font;
}
