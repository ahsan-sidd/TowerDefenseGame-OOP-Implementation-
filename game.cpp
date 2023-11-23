#include "game.hpp"
#include "Char.hpp"
#include "HealthBar.hpp"
// #include 

Game::Game(){};
Game::~Game(){};

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
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
    }
	gameMusic = Mix_LoadMUS("Assets/vanguard-epic-powerful-dark-orchestral.mp3");

	if (gameMusic == nullptr)
	{
		printf("Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
    }
	menuMusic = Mix_LoadMUS("Assets/never-forget.mp3");

	if (menuMusic == nullptr)
	{
		printf("Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;
	
	assets = loadTexture("Assets/Samurai/Walk.png");
    gTexture = loadTexture("Assets/Backgrounds/4_new.png");
	if(assets==NULL || gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(assets);
	assets=NULL;
	SDL_DestroyTexture(gTexture);
	
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	Mix_FreeMusic(gameMusic);
	gRenderer = NULL;
	//Quit SDL subsystems
	Mix_CloseAudio();
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

bool Game::StartScreen(){
    assets = loadTexture("Assets/Backgrounds/pixel-jess-night-market-start-rng.gif");
    SDL_Texture* startButton = loadTexture("Assets/yo.png");
	SDL_Texture* intro = loadTexture("Assets/Backgrounds/Intro.png");
	
	SDL_Texture* blackScreen = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderTarget(gRenderer, blackScreen);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); // Set the color to black
    SDL_RenderClear(gRenderer); // Fill the texture with the black color
    SDL_SetRenderTarget(gRenderer, NULL);
	Mix_PlayMusic(menuMusic, -1);


	if (startButton == NULL) {
		printf("Failed to load start button texture!\n");
		return false;
	}

    SDL_Rect startButtonRect;
    startButtonRect.x = (1244-222)/2/* x position of the start button */;
    startButtonRect.y = 590/* y position of the start button */;
    startButtonRect.w = 222/* width of the start button */;  //222
    startButtonRect.h = 83/* height of the start button */;   //83

	SDL_Rect introRect;
	introRect.x = 120/* x position of the start button */;
	introRect.y = 330/* y position of the start button */;
	introRect.w = 1020;//222/* width of the start button */;
	introRect.h = 150;//83/* height of the start button */;

    bool quit = false;
    bool renderButton = true;
    SDL_Event e;

	SDL_SetTextureBlendMode(startButton, SDL_BLENDMODE_BLEND);
	int alpha = 255;
	int alphaChange = -5;

	SDL_SetTextureBlendMode(intro, SDL_BLENDMODE_BLEND);
	// SDL_SetTextureAlphaMod(intro, 255);
	int introAlpha = 0;

	while (!quit) {
		if (renderButton){
			SDL_RenderCopy(gRenderer, blackScreen, NULL, NULL);

			SDL_SetTextureAlphaMod(intro, introAlpha);
			SDL_RenderCopy(gRenderer, intro, NULL, &introRect);
			while(SDL_PollEvent(&e) != 0){
				if (e.type == SDL_QUIT){
					quit = true;
					return false;
				}
				if (e.type == SDL_MOUSEBUTTONDOWN){
					renderButton = false;
				}
			}
			introAlpha += 1;
			if (introAlpha >= 255){
				introAlpha = 255;
				// introAlpha -= rand() % 1 - 5;
				
			}
			SDL_RenderPresent(gRenderer);
			SDL_Delay(10);
			continue;
		}

    	while (SDL_PollEvent(&e) != 0) {
        	if (e.type == SDL_QUIT) {
            	quit = true;
				return false;
        	}
        	if (e.type == SDL_MOUSEBUTTONDOWN) {
            	int xMouse, yMouse;
            	SDL_GetMouseState(&xMouse, &yMouse);
            	if (xMouse >= startButtonRect.x && xMouse <= startButtonRect.x + startButtonRect.w && yMouse >= startButtonRect.y && yMouse <= startButtonRect.y + startButtonRect.h) {
					Mix_FreeMusic(menuMusic);
					Mix_PlayMusic(gameMusic, -1);
                	quit = true;
            	}
        	}
    	}

    SDL_RenderCopy(gRenderer, assets, NULL, NULL);

    SDL_SetTextureAlphaMod(startButton, alpha);
    SDL_RenderCopy(gRenderer, startButton, NULL, &startButtonRect);

    SDL_RenderPresent(gRenderer);

    alpha += alphaChange;
    if (alpha <= 0 || alpha >= 255) {
        alphaChange = rand() % 11 - 5; // Random number between -5 and 5
        // alpha = std::clamp(alpha, 0, 255); // Ensure alpha stays within the valid range
    }
	}

    SDL_DestroyTexture(startButton);
	SDL_DestroyTexture(intro);
	SDL_DestroyTexture(blackScreen);
	return true;
}

void Game::run( )
{
	bool quit = false;
	SDL_Event e;

	int level = 2;

	CharacterState currentState = WALKING;

	// char* fontpath = "FreeSans.ttf";
	// TTF_Init();
	// TTF_Font *Font = TTF_OpenFont(fontpath, 24);

	HealthBar healthbar(gRenderer, 1000, 180, 200, 200);

	while( !quit )
	{
		if (gTexture != nullptr){
			SDL_DestroyTexture(gTexture);
			gTexture = nullptr;
		}
		std::string backgroundPath = "Assets/Backgrounds/Level" + std::to_string(level) + ".png";
		gTexture = loadTexture(backgroundPath);
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			if(e.type == SDL_MOUSEBUTTONDOWN){
			//this is a good location to add pigeon in linked list.
				if (e.button.button == SDL_BUTTON_LEFT){
					int xMouse, yMouse;
					SDL_GetMouseState(&xMouse,&yMouse);
					createNinja(xMouse, yMouse);
					level += 1;
					// std::cout << "Level: " << level << std::endl;
				}
				else if (e.button.button == SDL_BUTTON_RIGHT){
					int xMouse, yMouse;
					SDL_GetMouseState(&xMouse,&yMouse);
					createFighter(xMouse, yMouse);
					level -= 1;
					// std::cout << "Level: " << level << std::endl;
				}
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
			
		}


		SDL_RenderClear(gRenderer); //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
		//***********************draw the objects here********************

		switch (currentState){
			case WALKING:
				assets = loadTexture("Assets/Samurai/Walk.png");
				Walking(gRenderer, assets);
				assets = loadTexture("Assets/Fighter/Walk.png");
				WalkingFighter(gRenderer, assets);
				break;
			case ATTACKING:
				assets = loadTexture("Assets/Samurai/Attack_3.png");
				Attacking3(gRenderer, assets);
				healthbar.reduce_health();
				assets = loadTexture("Assets/Fighter/Attack_2.png");
				FighterAttacking2(gRenderer, assets);
				break;
		}
		// Walking(gRenderer, assets);

		//****************************************************************
		healthbar.render();

    	SDL_RenderPresent(gRenderer); //displays the updated renderer

	    SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds

	}
			
}
