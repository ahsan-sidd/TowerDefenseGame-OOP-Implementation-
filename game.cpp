#include "game.hpp"
#include "Char.hpp"

bool GameMenu::init() {
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

SDL_Texture* GameMenu::loadTexture(std::string path) {
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

GameMenu::GameMenu() : startButtonTexture(nullptr), endButtonTexture(nullptr) {
    // Load texture for start button
    startButtonTexture = loadTexture("Assets/start_button.png");
    if (startButtonTexture == nullptr) {
        printf("Failed to load start button texture!\n");
    }

    // Load texture for end button
    endButtonTexture = loadTexture("Assets/end_button.png");
    if (endButtonTexture == nullptr) {
        printf("Failed to load end button texture!\n");
    }

    // Set the positions and dimensions of the buttons
    startButtonRect = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 100};
    endButtonRect = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50, 200, 100};
}

GameMenu::~GameMenu() {
    // Free textures
    SDL_DestroyTexture(startButtonTexture);
    SDL_DestroyTexture(endButtonTexture);
}

void GameMenu::displayMenu(SDL_Renderer* renderer) {
    // Render start button
    SDL_RenderCopy(renderer, startButtonTexture, NULL, &startButtonRect);

    // Render end button
    SDL_RenderCopy(renderer, endButtonTexture, NULL, &endButtonRect);
}

bool GameMenu::handleEvents(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int xMouse, yMouse;
        SDL_GetMouseState(&xMouse, &yMouse);

        // Check if the mouse click is within the start button
        if (xMouse >= startButtonRect.x && xMouse <= startButtonRect.x + startButtonRect.w &&
            yMouse >= startButtonRect.y && yMouse <= startButtonRect.y + startButtonRect.h) {
            return true;  // Start the game
        }

        // Check if the mouse click is within the end button
        if (xMouse >= endButtonRect.x && xMouse <= endButtonRect.x + endButtonRect.w &&
            yMouse >= endButtonRect.y && yMouse <= endButtonRect.y + endButtonRect.h) {
            return true;  // End the game
        }
    }

    return false;
}





Game::Game(){};
Game::~Game(){};

bool Game::init() {
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

bool Game::loadMedia() {
    //Loading success flag
	bool success = true;
	
	assets = loadTexture("Assets/Attack_3.png");
    gTexture = loadTexture("Assets/Waterfall1.png");
	if(assets==NULL || gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
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

void Game::close() {
    //Free loaded images
	SDL_DestroyTexture(assets);
	assets=NULL;
	SDL_DestroyTexture(gTexture);
	
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::run() {
    bool quit = false;
	SDL_Event e;
    while (!quit) {
        switch (gameState) {
            case GameState::MENU:
                gameMenu.displayMenu(gRenderer);
                quit = gameMenu.handleEvents(e);
                break;
            case GameState::PLAYING:
                quit = handleEvents();
                break;
            case GameState::QUIT:
                quit = true;
                break;
        }

		SDL_RenderPresent(gRenderer); //displays the updated renderer

	    SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds
    }
	
}

bool Game::handleEvents() {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return true;
        }

        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse, &yMouse);
            createObject(xMouse, yMouse);
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                std::cout << "UP pressed" << std::endl;
                Jump(gRenderer, assets);
                break;
            case SDLK_DOWN:
                dropDown(gRenderer, assets);
                std::cout << "Down pressed" << std::endl;
                break;
            case SDLK_RIGHT:
                moveRight(gRenderer, assets);
                std::cout << "Right pressed" << std::endl;
                break;
            case SDLK_LEFT:
                moveLeft(gRenderer, assets);
                std::cout << "Left pressed" << std::endl;
                break;
            case SDLK_SPACE:
                Jump(gRenderer, assets);
                std::cout << "Space pressed" << std::endl;
                break;
            }
        }
    }
	SDL_RenderClear(gRenderer); //removes everything from renderer
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
		//***********************draw the objects here********************

	drawObjects(gRenderer, assets);

    return false;
}


