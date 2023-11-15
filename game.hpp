#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

enum GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

class Menu {
public:
    Menu(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~Menu();

    void handleEvents(SDL_Event& e);
    void render();

    GameState getCurrentState() const { return currentState; }
    SDL_Texture* loadTexture( std::string path );

private:
    SDL_Renderer* gRenderer;
    SDL_Texture* menuBackgroundTexture;
    SDL_Texture* startGameButtonTexture;
    SDL_Rect startGameButtonRect;
    GameState currentState;
};



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
    
    Menu* menu = NULL;

    // Add additional member variables for the start menu
    SDL_Texture* startMenuBackgroundTexture;
    SDL_Texture* startMenuButtonTexture;
    SDL_Rect startMenuButtonRect;
public:
    Game();
    ~Game();
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    void run();
};

