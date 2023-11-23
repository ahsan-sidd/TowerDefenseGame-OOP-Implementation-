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

class MouseClick {
public:
    MouseClick();
    ~MouseClick();
    bool init(SDL_Renderer* renderer);
    void handleEvent(SDL_Event& e);
    void render();
    void playClickSound();

private:
    Mix_Chunk* clickSound=NULL;
    SDL_Renderer* renderer=NULL;
    SDL_Texture* cursorTexture=NULL;
    SDL_Rect cursorRect;
    const int SCREEN_WIDTH = (1244); //1000    826     414    896
    const int SCREEN_HEIGHT = (817); //600;   734     670    640
    SDL_Texture* loadTexture(const std::string& path);
};