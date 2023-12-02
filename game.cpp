#include "game.hpp"
#include "Char.hpp"
#include "HealthBar.hpp"
#include "Breakthrough.hpp"
#include <string>
// #include 

Game::Game(){};
Game::~Game(){};
SDL_Texture* Game::assets = nullptr;
SDL_Renderer* Game::gRenderer = nullptr;

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
		gWindow = SDL_CreateWindow( "BreakThrough", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		// SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
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
				// SDL_RenderSetLogicalSize(gRenderer, 1080, 720);
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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
	gameMusic = Mix_LoadMUS("Assets/op.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 3);

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
	if (!mouseClick.init(gRenderer)) {
        printf("Failed to initialize MouseClick!\n");
        return false;
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
	// SDL_DestroyRenderer( mRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	Mix_FreeMusic(gameMusic);
	gameMusic = NULL;
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

	SDL_ShowCursor(SDL_DISABLE);

    assets = loadTexture("Assets/Backgrounds/5.png");
    SDL_Texture* startButton = loadTexture("Assets/Backgrounds/StartButton.png");
	SDL_Texture* intro = loadTexture("Assets/Backgrounds/Intro.png");
	SDL_Texture* clouds = loadTexture("Assets/Backgrounds/Clouds.png");
	SDL_Texture* title = loadTexture("Assets/Backgrounds/Title.png");
	SDL_Texture* samuraiStart = loadTexture("Assets/Samurai/Run.png");
	SDL_Texture* samuraiJump = loadTexture("Assets/Samurai/Jump.png");
	SDL_Texture* shinobiStart = loadTexture("Assets/Shinobi/Run.png");
	SDL_Texture* shinobiJump = loadTexture("Assets/Shinobi/Jump.png");
	SDL_Texture* fighterStart = loadTexture("Assets/Fighter/Run.png");
	SDL_Texture* fighterJump = loadTexture("Assets/Fighter/Jump.png");
	SDL_Texture* ocean = loadTexture("Assets/Backgrounds/Ocean.png");

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

	Mix_Chunk* jumpSound = Mix_LoadWAV("Assets/Jump.wav");
	if (jumpSound == nullptr) {
		printf("Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	Mix_VolumeChunk(jumpSound, MIX_MAX_VOLUME / 1.5);


    SDL_Rect startButtonRect;
    startButtonRect.x = (1244-270)/* x position of the start button */;
    startButtonRect.y = 400/* y position of the start button */;
    startButtonRect.w = 222/* width of the start button */;
    startButtonRect.h = 83/* height of the start button */;

	SDL_Rect introRect;
	introRect.x = SCREEN_WIDTH*0.096;//120/* x position of the start button */;
	introRect.y = SCREEN_HEIGHT*0.404;//330/* y position of the start button */;
	introRect.w = SCREEN_WIDTH*0.82;//1020;//222/* width of the start button */;
	introRect.h = SCREEN_HEIGHT*0.184;//150;//83/* height of the start button */;

	SDL_Rect cloudRect;
	cloudRect.x = 0;
	cloudRect.y = 0;
	cloudRect.w = SCREEN_WIDTH;
	cloudRect.h = SCREEN_HEIGHT;

	SDL_Rect oceanRect;
	oceanRect.x = 0;
	oceanRect.y = 0;
	oceanRect.w = SCREEN_WIDTH;
	oceanRect.h = SCREEN_HEIGHT;

	SDL_Rect titleRect;
	titleRect.x = 0;
	titleRect.y = 400;
	titleRect.w = 555;
	titleRect.h = 83;

	SDL_Rect CharacterSrc;
	CharacterSrc = {0, 0, 128, 128};
	// int CharacterWidth = 160;//128*scaleFactor;
	// int CharacterHeight = 160;//128*scaleFactor;
	// int characterX = SCREEN_WIDTH*positionFactorX;
	// int characterY = SCREEN_HEIGHT*positionFactorY;
	int samuraiYVelocity = 0;
	bool samuraiJumping = false;
	SDL_Rect samuraiRect = {50, 558, 160, 160};

	int shinobiYVelocity = 0;
	bool shinobiJumping = false;
	SDL_Rect shinobiRect = {150, 558, 160, 160};

	int fighterYVelocity = 0;
	bool fighterJumping = false;
	SDL_Rect fighterRect = {250, 558, 160, 160};
	// Character.moverRect = {characterX, characterY, CharacterWidth, CharacterHeight};


    bool quit = false;
    bool renderButton = true;
    SDL_Event e;

	SDL_SetTextureBlendMode(startButton, SDL_BLENDMODE_BLEND);
	int alpha = 255;
	int alphaChange = -5;

	SDL_SetTextureBlendMode(intro, SDL_BLENDMODE_BLEND);
	// SDL_SetTextureAlphaMod(intro, 255);
	int introAlpha = 0;

	int frameCount = 0;
	int characterFrame = 8;
	int animationDelay = 0;


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
				//on window resizing adjust rects relative to window size
				else if (e.type == SDL_WINDOWEVENT){
					if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
						int w = e.window.data1;
						int h = e.window.data2;
						introRect.x = w*0.096;//120/* x position of the start button */;
						introRect.y = h*0.404;//330/* y position of the start button */;
						introRect.w = w*0.82;//1020;//222/* width of the start button */;
						introRect.h = h*0.184;//150;//83/* height of the start button */;
					}
				}
			}
			introAlpha += 1;
			if (introAlpha >= 255){
				introAlpha = 255;
				// introAlpha -= rand() % 1 - 5;
				
			}
			mouseClick.render(gRenderer);
			SDL_RenderPresent(gRenderer);
			SDL_Delay(15);
			continue;
		}

    	while (SDL_PollEvent(&e) != 0) {
			mouseClick.handleEvent(e);
        	if (e.type == SDL_QUIT) {
            	quit = true;
				return false;
        	}
        	if (e.type == SDL_MOUSEBUTTONDOWN) {
            	int xMouse, yMouse;
            	SDL_GetMouseState(&xMouse, &yMouse);
            	if (xMouse >= startButtonRect.x && xMouse <= startButtonRect.x + startButtonRect.w && yMouse >= startButtonRect.y && yMouse <= startButtonRect.y + startButtonRect.h) {
					Mix_FreeMusic(menuMusic);
					Mix_CloseAudio();
					Mix_PlayMusic(gameMusic, -1);
					quit = true;
            	}
				else if (xMouse >= samuraiRect.x+30 && xMouse <= samuraiRect.x + samuraiRect.w-30 && yMouse >= samuraiRect.y+30 && yMouse <= samuraiRect.y + samuraiRect.h-30) {
       				samuraiYVelocity = -20; // Adjust as needed
        			samuraiJumping = true;
					// characterFrame = 12;
					Mix_PlayChannel(-1, jumpSound, 0);
    			}
				else if (xMouse >= shinobiRect.x+30 && xMouse <= shinobiRect.x + shinobiRect.w-30 && yMouse >= shinobiRect.y+30 && yMouse <= shinobiRect.y + shinobiRect.h-30) {
	   				shinobiYVelocity = -20; // Adjust as needed
					shinobiJumping = true;
					// characterFrame = 12;
					Mix_PlayChannel(-1, jumpSound, 0);
        		}
				else if (xMouse >= fighterRect.x+30 && xMouse <= fighterRect.x + fighterRect.w-30 && yMouse >= fighterRect.y+30 && yMouse <= fighterRect.y + fighterRect.h-30) {
					fighterYVelocity = -20; // Adjust as needed
					fighterJumping = true;
					// characterFrame = 12;
					Mix_PlayChannel(-1, jumpSound, 0);
				}
			}
			else if (e.type == SDL_WINDOWEVENT){
				if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
					int w = e.window.data1;
					int h = e.window.data2;
					cloudRect.w = w;
					cloudRect.h = h;
					// cloudRect2.w = w;
					// cloudRect2.h = h*1.004;
				}
			}
    	}

	cloudRect.x -= 1;
	oceanRect.x -= 1;
	if (cloudRect.x < 0){
		cloudRect.x = SCREEN_WIDTH;
		oceanRect.x = SCREEN_WIDTH;
	}
	SDL_Rect cloudRect2 = cloudRect;
	cloudRect2.x -= SCREEN_WIDTH;
	SDL_Rect oceanRect2 = oceanRect;
	oceanRect2.x -= SCREEN_WIDTH;

    SDL_RenderCopy(gRenderer, assets, NULL, NULL);
	SDL_RenderCopy(gRenderer, clouds, NULL, &cloudRect2);
	SDL_RenderCopy(gRenderer, clouds, NULL, &cloudRect);

	SDL_RenderCopy(gRenderer, ocean, NULL, &oceanRect);
	SDL_RenderCopy(gRenderer, ocean, NULL, &oceanRect2);

	SDL_RenderCopy(gRenderer, title, NULL, &titleRect);

	if (samuraiYVelocity < 20 and samuraiJumping){
		samuraiYVelocity += 1;
	}

	// Always check if the character has reached the ground
	samuraiRect.y += samuraiYVelocity;
	if (samuraiRect.y >= 558){
		samuraiRect.y = 558;
		samuraiJumping = false;
		samuraiYVelocity = 0; // Reset the velocity so the character doesn't continue to move downwards
		// characterFrame = 8;
	}

	// Render the character with the current texture
	if (samuraiJumping){
		SDL_RenderCopy(gRenderer, samuraiJump, &CharacterSrc, &samuraiRect);
	}
	else{
		SDL_RenderCopy(gRenderer, samuraiStart, &CharacterSrc, &samuraiRect);   
	}
	// SDL_RenderCopy(gRenderer, samuraiStart, &CharacterSrc, &samuraiRect);
	// CharacterMover.x += 100;
	if (shinobiYVelocity < 20 and shinobiJumping){
		shinobiYVelocity += 1;
	}
	shinobiRect.y += shinobiYVelocity;
	if (shinobiRect.y >= 558){
		shinobiRect.y = 558;
		shinobiJumping = false;
		shinobiYVelocity = 0; // Reset the velocity so the character doesn't continue to move downwards
	}
	if (shinobiJumping){
		SDL_RenderCopy(gRenderer, shinobiJump, &CharacterSrc, &shinobiRect);
	}
	else{
		SDL_RenderCopy(gRenderer, shinobiStart, &CharacterSrc, &shinobiRect);   
	}
	// SDL_RenderCopy(gRenderer, shinobiStart, &CharacterSrc, &shinobiRect);
	// CharacterMover.x += 100;
	if (fighterYVelocity < 20 and fighterJumping){
		fighterYVelocity += 1;
	}
	fighterRect.y += fighterYVelocity;
	if (fighterRect.y >= 558){
		fighterRect.y = 558;
		fighterJumping = false;
		fighterYVelocity = 0; // Reset the velocity so the character doesn't continue to move downwards
	}
	if (fighterJumping){
		SDL_RenderCopy(gRenderer, fighterJump, &CharacterSrc, &fighterRect);
	}
	else{
		SDL_RenderCopy(gRenderer, fighterStart, &CharacterSrc, &fighterRect);   
	}
	// SDL_RenderCopy(gRenderer, fighterStart, &CharacterSrc, &fighterRect);
	// CharacterMover.x = 50;

	if (animationDelay == 6){

	frameCount++;
	if (frameCount % 8 == 0){
		CharacterSrc.x = 0;
		CharacterSrc.y = 0;
	}
	else{
		CharacterSrc.x += 128;
	}
		// Character.srcRect.x += 128;
		animationDelay = 0;
	}
	animationDelay++;


    SDL_SetTextureAlphaMod(startButton, alpha);
    SDL_RenderCopy(gRenderer, startButton, NULL, &startButtonRect);

	mouseClick.render(gRenderer);

    SDL_RenderPresent(gRenderer);

    alpha += alphaChange;
    if (alpha <= 0 || alpha >= 255) {
        alphaChange = rand() % 11 - 5; // Random number between -5 and 5
        // alpha = std::clamp(alpha, 0, 255); // Ensure alpha stays within the valid range
    }
	SDL_Delay(10);
	}

	Mix_FreeChunk(jumpSound);

	SDL_DestroyTexture(samuraiStart);
	SDL_DestroyTexture(samuraiJump);
	SDL_DestroyTexture(shinobiStart);
	SDL_DestroyTexture(shinobiJump);
	SDL_DestroyTexture(fighterStart);
	SDL_DestroyTexture(fighterJump);
    SDL_DestroyTexture(startButton);
	SDL_DestroyTexture(intro);
	SDL_DestroyTexture(blackScreen);
	SDL_DestroyTexture(clouds);
	SDL_DestroyTexture(title);
	SDL_DestroyTexture(ocean);
	return true;
}

void Game::run( )
{
	GameState currentState = GAME;

	bool quit = false;
	SDL_Event e;

	int level = 2;

	Breakthrough breakthrough;

	Uint32 current_time;
	Uint32 bullet_time = SDL_GetTicks();

	assets = loadTexture("Assets/Samurai/Walk.png");

	// CharacterState currentState = WALKING;

	// char* fontpath = "FreeSans.ttf";
	// TTF_Init();
	// TTF_Font *Font = TTF_OpenFont(fontpath, 24);

	HealthBar healthbar(gRenderer, 1000, 180, 200, 200);

	Menu menu;
	if (!menu.init(gRenderer)) {
		printf("Failed to initialize Menu!\n");
	}
	while( !quit )
	{
		current_time = SDL_GetTicks();
		if (gTexture != nullptr){
			SDL_DestroyTexture(gTexture);
			gTexture = nullptr;
		}
		std::string backgroundPath = "Assets/Backgrounds/Level" + std::to_string(level) + ".png";
		gTexture = loadTexture(backgroundPath);
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{	
			mouseClick.handleEvent(e);
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			if (menu.handleEvent(e)){
				currentState = MENU;
			}
			else if (currentState == MENU && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            // The escape key was pressed while in the menu state, switch back to the gameplay state
            currentState = GAME;
        	}
			if(e.type == SDL_MOUSEBUTTONDOWN){
			//this is a good location to add pigeon in linked list.
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					int xMouse, yMouse;
					SDL_GetMouseState(&xMouse,&yMouse);
					breakthrough.createObject(xMouse, yMouse, "character");
					// level += 1;
					// std::cout << "Level: " << level << std::endl;
				}
			}
				// else if (e.button.button == SDL_BUTTON_RIGHT){
				// 	int xMouse, yMouse;
				// 	SDL_GetMouseState(&xMouse,&yMouse);
				// 	createFighter(xMouse, yMouse);
				// 	level -= 1;
				// 	// std::cout << "Level: " << level << std::endl;
				// }
			
			// else if (e.type == SDL_KEYDOWN)
			// {
			// 	switch(e.key.keysym.sym){
			// 	case (SDLK_UP):
			// 	std::cout << "UP pressed" << std::endl;
			// 	// assets = loadTexture("Assets/Samurai/Walk.png");
			// 	// Walking(gRenderer, assets);
			// 	// Jump(gRenderer, assets);
			// 	currentState = ATTACKING;
			// 	break;

			// 	case (SDLK_DOWN):
			// 	// dropDown(gRenderer, assets);
			// 	std::cout << "Down pressed" << std::endl;
			// 	currentState = WALKING;
			// 	// assets = loadTexture("Assets/Samurai/Attack_3.png");
			// 	// Attacking3(gRenderer, assets);
			// 	break;

			// 	case (SDLK_RIGHT):
			// 	moveRight(gRenderer, assets);
			// 	std::cout << "Right pressed" << std::endl;
			// 	break;

			// 	case (SDLK_LEFT):
			// 	moveLeft(gRenderer, assets);
			// 	std::cout << "Left pressed" << std::endl;
			// 	break;

			// 	case (SDLK_SPACE):
			// 	Jump(gRenderer, assets);
			// 	std::cout << "Space pressed" << std::endl;
			// 	break;
			// 	}
			// }
			
		}

		SDL_RenderClear(gRenderer); //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
		
		if (current_time - bullet_time >= 2000)
		{
			breakthrough.createObject(800, 400, "bullet");
			bullet_time = current_time;
		}
		breakthrough.drawObjects();

		//***********************draw the objects here********************

		// switch (currentState){
		// 	case WALKING:
		// 		assets = loadTexture("Assets/Samurai/Walk.png");
		// 		Walking(gRenderer, assets);
		// 		assets = loadTexture("Assets/Fighter/Walk.png");
		// 		WalkingFighter(gRenderer, assets);
		// 		break;
		// 	case ATTACKING:
		// 		assets = loadTexture("Assets/Samurai/Attack_3.png");
		// 		Attacking3(gRenderer, assets);
		// 		healthbar.reduce_health();
		// 		assets = loadTexture("Assets/Fighter/Attack_2.png");
		// 		FighterAttacking2(gRenderer, assets);
		// 		break;
		// }
		// Walking(gRenderer, assets);

		//****************************************************************
		if (currentState == MENU){
			menu.renderMenuScreen(gRenderer, e);
			mouseClick.render(gRenderer);
			SDL_RenderPresent(gRenderer);
			SDL_Delay(10);
			continue;
		}


		menu.render(gRenderer);
		mouseClick.render(gRenderer);
		healthbar.render();

    	SDL_RenderPresent(gRenderer); //displays the updated renderer

	    SDL_Delay(10);	//causes sdl engine to delay for specified miliseconds
		//SDL_Delay can be lowered to 10-20 for smoother animation
	}
			
}
