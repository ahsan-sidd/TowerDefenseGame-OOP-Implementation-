#include "game.hpp"
#include "Char.hpp"

Menu::~Menu() {
    // Free menu textures
    SDL_DestroyTexture(menuBackgroundTexture);
    SDL_DestroyTexture(startGameButtonTexture);
}

SDL_Texture* Menu::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}
Menu::Menu(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : gRenderer(renderer), currentState(MENU) {
    // Load menu background and start game button textures
    menuBackgroundTexture = loadTexture("Backgrounds/4.png");
    startGameButtonTexture = loadTexture("Assets/start_button.png");

    // Set the position and size of the start game button
    startGameButtonRect.x = screenWidth / 2 - 50;
    startGameButtonRect.y = screenHeight / 2 - 25;
    startGameButtonRect.w = 100;
    startGameButtonRect.h = 50;
}

void Menu::handleEvents(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int xMouse, yMouse;
        SDL_GetMouseState(&xMouse, &yMouse);

        // Check if the mouse click is within the start game button area
        if (xMouse > startGameButtonRect.x && xMouse < startGameButtonRect.x + startGameButtonRect.w &&
            yMouse > startGameButtonRect.y && yMouse < startGameButtonRect.y + startGameButtonRect.h) {
            currentState = PLAYING; // Start the game when the button is clicked
        }
    }
}

void Menu::render() {
    // Render menu background and start game button
    SDL_RenderCopy(gRenderer, menuBackgroundTexture, NULL, NULL);
    SDL_RenderCopy(gRenderer, startGameButtonTexture, NULL, &startGameButtonRect);
}


Game::Game(){};
Game::~Game(){};

enum CharacterState{
	WALKING,
	ATTACKING
};

bool Game::init()
{
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "BreakThrough", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;
	
	assets = loadTexture("Assets/Samurai/Walk.png");
    gTexture = loadTexture("Assets/Backgrounds/4_new.png");
	startMenuBackgroundTexture = loadTexture("Assets/Menu/Background.png");
    startMenuButtonTexture = loadTexture("Assets/Menu/StartButton.png");
    menu = new Menu(gRenderer, 1244, 817);
	if(assets==NULL || gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}

void Game::close()
{
	delete menu;
	//Free loaded images
	SDL_DestroyTexture(assets);
	assets=NULL;
	SDL_DestroyTexture(gTexture);
	
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	SDL_DestroyTexture(startMenuBackgroundTexture);
    SDL_DestroyTexture(startMenuButtonTexture);
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}
void Game::run( )
{
	bool quit = false;
	SDL_Event e;

	CharacterState currentState = WALKING;
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			switch (menu->getCurrentState()) {
                case MENU:
                    menu->handleEvents(e);
                    break;

                case PLAYING:
                    if(e.type == SDL_MOUSEBUTTONDOWN){
					//this is a good location to add pigeon in linked list.
						int xMouse, yMouse;
						SDL_GetMouseState(&xMouse,&yMouse);
						createObject(xMouse, yMouse);
					}
					else if (e.type == SDL_KEYDOWN){
						switch(e.key.keysym.sym){
						case (SDLK_UP):
						std::cout << "UP pressed" << std::endl;
						// assets = loadTexture("Assets/Samurai/Walk.png");
						// Walking(gRenderer, assets);
						// Jump(gRenderer, assets);
						currentState = ATTACKING;
						break;

						case (SDLK_DOWN):
						// dropDown(gRenderer, assets);
						std::cout << "Down pressed" << std::endl;
						currentState = WALKING;
						// assets = loadTexture("Assets/Samurai/Attack_3.png");
						// Attacking3(gRenderer, assets);
						break;

						case (SDLK_RIGHT):
						moveRight(gRenderer, assets);
						std::cout << "Right pressed" << std::endl;
						break;

						case (SDLK_LEFT):
						moveLeft(gRenderer, assets);
						std::cout << "Left pressed" << std::endl;
						break;

						case (SDLK_SPACE):
						Jump(gRenderer, assets);
						std::cout << "Space pressed" << std::endl;
						break;
						}
					}
                    break;
            }
			
		}


		SDL_RenderClear(gRenderer); //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
		//***********************draw the objects here********************
		switch (menu->getCurrentState()) {
            case MENU:
                menu->render(); // Render the start menu instead of the regular menu
                break;

            case PLAYING:
                switch (currentState){
					case WALKING:
						assets = loadTexture("Assets/Samurai/Walk.png");
						Walking(gRenderer, assets);
						break;
					case ATTACKING:
						assets = loadTexture("Assets/Samurai/Attack_3.png");
						Attacking3(gRenderer, assets);
						break;
				}
                break;
        }
		// Walking(gRenderer, assets);

		//****************************************************************
    	SDL_RenderPresent(gRenderer); //displays the updated renderer

	    SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds
	}
			
}