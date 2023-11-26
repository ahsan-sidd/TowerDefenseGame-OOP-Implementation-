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
    bool init(SDL_Renderer* gRenderer);
    void handleEvent(SDL_Event& e);
    void render(SDL_Renderer* gRenderer);
    void playClickSound();

private:
    SDL_Rect cursorRect;
    SDL_Texture* cursorTexture=NULL;
    Mix_Chunk* clickSound=NULL;
    // SDL_Renderer* renderer=NULL;
    const int SCREEN_WIDTH = (1244); //1000    826     414    896
    const int SCREEN_HEIGHT = (817); //600;   734     670    640
    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
};