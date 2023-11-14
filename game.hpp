#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>


class GameMenu {
public:
    GameMenu();
    ~GameMenu();
    bool init();
    bool handleEvents(SDL_Event& e);
    void displayMenu(SDL_Renderer* gRenderer);
    SDL_Texture* loadTexture(std::string path);

private:
    const int SCREEN_WIDTH = (896); //1000    826     414
    const int SCREEN_HEIGHT = (640); //600;   734     670
    SDL_Texture* startButtonTexture;
    SDL_Texture* endButtonTexture;
    SDL_Rect startButtonRect;
    SDL_Rect endButtonRect;
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    //global reference to png image sheets
    SDL_Texture* assets=NULL;
    


};

class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = (896); //1000    826     414
    const int SCREEN_HEIGHT = (640); //600;   734     670

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    //global reference to png image sheets
    SDL_Texture* assets=NULL;

    bool handleEvents();
    
    enum GameState {
        MENU,
        PLAYING,
        QUIT
    };

    GameState gameState;
    GameMenu gameMenu;
    

public:
    Game();
    ~Game();
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    void run();
};



