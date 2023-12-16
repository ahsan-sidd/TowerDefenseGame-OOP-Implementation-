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
#include "MouseClick.hpp"
#include "Menu.hpp"
#include "Tower.hpp"
// #include "cmath"
// #include "CustomCursor.cpp"

enum GameState{
        MENU,
        GAME,
        QUIT
    };

enum Character{
        SAMURAI,
        SHINOBI,
        FIGHTER
    };

class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = (1244); 
    const int SCREEN_HEIGHT = (818); 
    //ratio of actual value/1.8 is being used.  

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    // SDL_Renderer* gRenderer = NULL;
    // SDL_Renderer* mRenderer = NULL;


    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    //global reference to png image sheets
    // SDL_Texture* assets=NULL;

    Mix_Music* gameMusic=NULL;

    Mix_Music* menuMusic=NULL;

    MouseClick mouseClick;


    double scaleFactor = 0.5;
    double positionFactorX = 0.04;
    double positionFactorY = 0.68;

public:
    static SDL_Renderer* gRenderer;
    static SDL_Texture* assets;
    Game();
    ~Game();
    bool init();
    bool loadMedia();
    void close();
    static SDL_Texture* loadTexture( std::string path );
    bool StartScreen();
    bool characterSelect();
    void renderAttackAnimation(SDL_Texture* attackTexture, SDL_Texture* samuraiSelect, SDL_Texture* shinobiSelect, SDL_Texture* fighterSelect, SDL_Rect samuraiSrc, SDL_Rect shinobiSrc, SDL_Rect fighterSrc, SDL_Rect samuraiDest, SDL_Rect shinobiDest, SDL_Rect fighterDest, int CharNum);
    // void fadeOut();
    void renderText(const std::string& text, int x, int y);
    void drawCharacterSelectScreen(SDL_Texture* samuraiSelect, SDL_Texture* shinobiSelect, SDL_Texture* fighterSelect, SDL_Rect samuraiSrc, SDL_Rect shinobiSrc, SDL_Rect fighterSrc, SDL_Rect samuraiDest, SDL_Rect shinobiDest, SDL_Rect fighterDest, int CharNum);
    bool run();
    static Character character;
    
    
};

