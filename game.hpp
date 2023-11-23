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

class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = (1244); //1000    826     414    896
    const int SCREEN_HEIGHT = (817); //600;   734     670    640
    //ratio of actual value/1.8 is being used.  

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    //global reference to png image sheets
    SDL_Texture* assets=NULL;

    Mix_Music* gameMusic=NULL;

    Mix_Music* menuMusic=NULL;
    

public:
    Game();
    ~Game();
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    bool StartScreen();
    void run();
};

