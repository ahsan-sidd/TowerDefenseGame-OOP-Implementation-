#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <SDL_mixer.h>

class Menu {
public:
    Menu();
    ~Menu();
    bool init(SDL_Renderer* gRenderer);
    bool handleEvent(SDL_Event& e);
    void render(SDL_Renderer* gRenderer);
    void renderMenuScreen(SDL_Renderer* gRenderer, SDL_Event& e);
private:
    bool isDragging = false;
    SDL_Rect sliderRect = {475, 314, 32, 32};
    int sliderStartX = sliderRect.x;
    int sliderEndX = sliderRect.x + 266;
    SDL_Rect MenuButtonRect;
    SDL_Texture* MenuNormalButtonTexture=NULL;
    SDL_Texture* MenuButtonTexture=NULL;
    SDL_Texture* MenuHoverButtonTexture=NULL;
    SDL_Texture* MenuTexture=NULL;
    const int SCREEN_WIDTH = (1244); //1000    826     414    896
    const int SCREEN_HEIGHT = (818); //600;   734     670    640
    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
};