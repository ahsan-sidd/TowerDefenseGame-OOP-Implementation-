#include "game.hpp"
#include "Char.hpp"
#include "HealthBar.hpp"
#include "Breakthrough.hpp"
#include <string>
#include "HealSpell.hpp"
#include "Ninja.hpp"

Character Game::character = SAMURAI;
Game::Game(){};
Game::~Game(){};
SDL_Texture* Game::assets = nullptr;
SDL_Renderer* Game::gRenderer = nullptr;

bool Game::init()
{
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
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

	if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
		return false;
	}


// Define tower properties (modify these according to your game logic)
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
	Mix_HaltMusic();
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
	
	Mix_Music* logoMusic = Mix_LoadMUS("Assets/epic_logo-2.mp3");
	Mix_PlayMusic(logoMusic, 1);




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
					Mix_FreeMusic(logoMusic);
					Mix_PlayMusic(menuMusic, -1);
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

bool Game::characterSelect(){

	// Define the source rectangles for the idle frames
    SDL_Rect samuraiSrc = {0, 0, 128, 128}; // Adjust these values as needed
    SDL_Rect shinobiSrc = {0, 0, 128, 128};
    SDL_Rect fighterSrc = {0, 0, 128, 128};

	// Define the destination rectangles for the characters
    SDL_Rect samuraiDest = {160, 330, 160, 160}; // Adjust these values as needed
    SDL_Rect shinobiDest = {480, 330, 160, 160};
    SDL_Rect fighterDest = {800, 330, 160, 160};

	// assets = loadTexture("Assets/Backgrounds/5.png");
	SDL_Texture* samuraiSelect = loadTexture("Assets/Samurai/Idle.png");
	SDL_Texture* shinobiSelect = loadTexture("Assets/Shinobi/Idle.png");
	SDL_Texture* fighterSelect = loadTexture("Assets/Fighter/Idle.png");

	SDL_Texture* fighterAttack = loadTexture("Assets/Fighter/Attack_3.png");
	SDL_Texture* samuraiAttack = loadTexture("Assets/Samurai/Attack_2.png");
	SDL_Texture* shinobiAttack = loadTexture("Assets/Shinobi/Attack_3.png");
	// SDL_Texture* blackScreen = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_Texture* characterSelect = loadTexture("Assets/Backgrounds/CharSelect.png");
	SDL_Texture* charTop = loadTexture("Assets/Backgrounds/CharTop.png");
	SDL_Rect charTopDest = {0, 0, 1244, 282};
	// Define the frame index and frame delay counter
    int frameIndex = 0;
    int frameDelay = 0;

	// Load the dialogue box texture
	SDL_Texture* dialogueBox = loadTexture("Assets/Backgrounds/DialogueBox.png");

	TTF_Font* font = TTF_OpenFont("Assets/Font.ttf", 24);
	if (font == NULL) {
		printf("Failed to load font: %s\n", TTF_GetError());
		return false;
	}

	std::string textSamurai = "Samurai";
	std::string textShinobi = "Shinobi";
	std::string textFighter = "Fighter";

	std::vector<SDL_Texture*> texturesSamurai;
	std::vector<SDL_Texture*> texturesShinobi;
	std::vector<SDL_Texture*> texturesFighter;

	for (char c : textSamurai) {
		std::string s(1, c);
		SDL_Surface* surface = TTF_RenderText_Solid(font, s.c_str(), {255, 255, 255});
		SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
		texturesSamurai.push_back(texture);
		SDL_FreeSurface(surface);
	}

	for (char c : textShinobi) {
		std::string s(1, c);
		SDL_Surface* surface = TTF_RenderText_Solid(font, s.c_str(), {255, 255, 255});
		SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
		texturesShinobi.push_back(texture);
		SDL_FreeSurface(surface);
	}

	for (char c : textFighter) {
		std::string s(1, c);
		SDL_Surface* surface = TTF_RenderText_Solid(font, s.c_str(), {255, 255, 255});
		SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
		texturesFighter.push_back(texture);
		SDL_FreeSurface(surface);
	}

	int textDelay = 0;
	int numChars = 0;

	bool quit = true;
	while (quit){
		SDL_RenderCopy(gRenderer, characterSelect, NULL, NULL);
		SDL_RenderCopy(gRenderer, samuraiSelect, &samuraiSrc, &samuraiDest);
        SDL_RenderCopy(gRenderer, shinobiSelect, &shinobiSrc, &shinobiDest);
        SDL_RenderCopy(gRenderer, fighterSelect, &fighterSrc, &fighterDest);
		SDL_RenderCopy(gRenderer, charTop, NULL, &charTopDest);

		int xMouse, yMouse;
		SDL_GetMouseState(&xMouse, &yMouse);

		// Show the dialogue box and type out the text when the mouse is over a character
		if (xMouse >= samuraiDest.x && xMouse <= samuraiDest.x + 160 && yMouse >= samuraiDest.y && yMouse <= samuraiDest.y + 160) {
			if (textDelay >= 3) {
				textDelay = 0;
				if (numChars < texturesSamurai.size()) {
					numChars++;
				}
			}
			textDelay++;

			for (int i = 0; i < numChars; i++) {
				SDL_Rect dest = {180 + i * 20, 500, 20, 25}; // Adjust these values as needed
				SDL_RenderCopy(gRenderer, texturesSamurai[i], NULL, &dest);
			}	

		}
		else if (xMouse >= shinobiDest.x && xMouse <= shinobiDest.x + 160 && yMouse >= shinobiDest.y && yMouse <= shinobiDest.y + 160) {
			// ...
			if (textDelay >= 3) {
				textDelay = 0;
				if (numChars < texturesShinobi.size()) {
					numChars++;
				}
			}
			textDelay++;

			for (int i = 0; i < numChars; i++) {
				SDL_Rect dest = {500 + i * 20, 500, 20, 25}; // Adjust these values as needed
				SDL_RenderCopy(gRenderer, texturesShinobi[i], NULL, &dest);
			}   
		} else if (xMouse >= fighterDest.x && xMouse <= fighterDest.x + 160 && yMouse >= fighterDest.y && yMouse <= fighterDest.y + 160) {
			// ...
			if (textDelay >= 3) {
				textDelay = 0;
				if (numChars < texturesFighter.size()) {
					numChars++;
				}
			}
			textDelay++;

			for (int i = 0; i < numChars; i++) {
				SDL_Rect dest = {820 + i * 20, 500, 20, 25}; // Adjust these values as needed
				SDL_RenderCopy(gRenderer, texturesFighter[i], NULL, &dest);
			}   
		}
		else{
			textDelay = 0;
			numChars = 0;
		}

			

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			mouseClick.handleEvent(e);
			if (e.type == SDL_QUIT) {
				quit = false;
				return false;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				int xMouse, yMouse;
				SDL_GetMouseState(&xMouse, &yMouse);
				if (xMouse >= 160 && xMouse <= 320 && yMouse >= 330 && yMouse <= 490) {
					Game::character = SAMURAI;
					Mix_Chunk* slashSound = Mix_LoadWAV("Assets/slash.wav");
					Mix_PlayChannel(-1, slashSound, 0);
					//reduce volume of slash sound
					Mix_VolumeChunk(slashSound, MIX_MAX_VOLUME / 3);
					renderAttackAnimation(samuraiAttack, samuraiSelect, shinobiSelect, fighterSelect, samuraiSrc, shinobiSrc, fighterSrc, samuraiDest, shinobiDest, fighterDest, 1);
					// fadeOut();
					Mix_FreeChunk(slashSound);
					quit = false;
					// return;
				}
				else if (xMouse >= 480 && xMouse <= 640 && yMouse >= 330 && yMouse <= 490) {
					Game::character = SHINOBI;
					Mix_Chunk* daggerSound = Mix_LoadWAV("Assets/dagger.wav");
					Mix_PlayChannel(-1, daggerSound, 0);
					renderAttackAnimation(shinobiAttack, samuraiSelect, shinobiSelect, fighterSelect, samuraiSrc, shinobiSrc, fighterSrc, samuraiDest, shinobiDest, fighterDest, 2);
					// fadeOut();
					Mix_FreeChunk(daggerSound);
					quit = false;
					// return;
				}
				else if (xMouse >= 800 && xMouse <= 960 && yMouse >= 330 && yMouse <= 490) {
					Game::character = FIGHTER;
					Mix_Chunk* kickSound = Mix_LoadWAV("Assets/kick.wav");
					Mix_PlayChannel(-1, kickSound, 0);
					Mix_VolumeChunk(kickSound, MIX_MAX_VOLUME / 2);
					renderAttackAnimation(fighterAttack, samuraiSelect, shinobiSelect, fighterSelect, samuraiSrc, shinobiSrc, fighterSrc, samuraiDest, shinobiDest, fighterDest, 3);
					// fadeOut();
					Mix_FreeChunk(kickSound);
					quit = false;
					// return;
				}
			}

		}

		frameDelay++;
		// If the frame delay counter reaches 6, reset it and increment the frame index
        if (frameDelay >= 6) {
            frameDelay = 0;
            frameIndex++;

            // If the frame index reaches 6, reset it to 0
            if (frameIndex >= 6) {
                frameIndex = 0;
            }
        }	

		samuraiSrc.x = shinobiSrc.x = fighterSrc.x = frameIndex * 128;




		// SDL_RenderCopy(gRenderer, samuraiText, &samuraiTextSrc, &samuraiTextDest);
		

		mouseClick.render(gRenderer);
		SDL_RenderPresent(gRenderer);
		SDL_Delay(10);
	}

	Mix_FreeMusic(menuMusic);
	Mix_CloseAudio();
	Mix_PlayMusic(gameMusic, -1);

	SDL_DestroyTexture(samuraiSelect);
	SDL_DestroyTexture(shinobiSelect);
	SDL_DestroyTexture(fighterSelect);
	SDL_DestroyTexture(characterSelect);
	SDL_DestroyTexture(dialogueBox);

	SDL_DestroyTexture(fighterAttack);
	SDL_DestroyTexture(samuraiAttack);
	SDL_DestroyTexture(shinobiAttack);
	// SDL_DestroyTexture(samuraiText);
	// SDL_FreeSurface(samuraiSurface);
	for (SDL_Texture* texture : texturesSamurai) {
    	SDL_DestroyTexture(texture);
	}
	for (SDL_Texture* texture : texturesShinobi) {
		SDL_DestroyTexture(texture);
	}
	for (SDL_Texture* texture : texturesFighter) {
		SDL_DestroyTexture(texture);
	}
	TTF_CloseFont(font);
	return true;

}

void Game::drawCharacterSelectScreen(SDL_Texture* samuraiSelect, SDL_Texture* shinobiSelect, SDL_Texture* fighterSelect, SDL_Rect samuraiSrc, SDL_Rect shinobiSrc, SDL_Rect fighterSrc, SDL_Rect samuraiDest, SDL_Rect shinobiDest, SDL_Rect fighterDest, int CharNum) {
	if (CharNum != 1){SDL_RenderCopy(gRenderer, samuraiSelect, &samuraiSrc, &samuraiDest);}
	if (CharNum != 2){SDL_RenderCopy(gRenderer, shinobiSelect, &shinobiSrc, &shinobiDest);}
	if (CharNum != 3){SDL_RenderCopy(gRenderer, fighterSelect, &fighterSrc, &fighterDest);}
}

void Game::renderAttackAnimation(SDL_Texture* attackTexture, SDL_Texture* samuraiSelect, SDL_Texture* shinobiSelect, SDL_Texture* fighterSelect, SDL_Rect samuraiSrc, SDL_Rect shinobiSrc, SDL_Rect fighterSrc, SDL_Rect samuraiDest, SDL_Rect shinobiDest, SDL_Rect fighterDest, int CharNum) {
	SDL_Rect src = {0, 0, 128, 128}; // Source rectangle for the frames
	SDL_Rect dest = {0,0,0,0};
	if (CharNum == 1){
		dest = {160, 330, 160, 160}; // Destination rectangle for the frames
	}
	else if (CharNum == 2){
		dest = {480, 330, 160, 160}; // Destination rectangle for the frames
	}
	else if (CharNum == 3){
		dest = {800, 330, 160, 160}; // Destination rectangle for the frames
	}
	// SDL_Rect dest = {160, 330, 160, 160}; // Destination rectangle for the frames

	// Set the renderer color to black (RGBA: 0, 0, 0, 255)
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);


	// Loop through the frames
	for (int i = 0; i < 4; i++) {

		// // Draw a black rectangle at the destination
		SDL_RenderFillRect(gRenderer, &dest);

		src.x = i * 128; // Update the x position of the source rectangle

		// Redraw the character select screen
		drawCharacterSelectScreen(samuraiSelect, shinobiSelect, fighterSelect, samuraiSrc, shinobiSrc, fighterSrc, samuraiDest, shinobiDest, fighterDest, CharNum);

		// Render the current frame
		SDL_RenderCopy(gRenderer, attackTexture, &src, &dest);

		// Update the screen
		SDL_RenderPresent(gRenderer);

		// Wait for a short delay
		SDL_Delay(120);
	}
}

// void Game::fadeOut() {
// 	SDL_Rect screenRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; // Rectangle covering the entire screen

// 	// Loop from 0 to 255, stepping by fadeSpeed
// 	int j = 255;
// 	for (int i = 0; i <= 255; i += 5) {
// 		// Set the renderer color to black with the current alpha value
// 		SDL_SetRenderDrawColor(gRenderer, i, i, i, j);

// 		// Draw a rectangle over the entire screen
// 		SDL_RenderFillRect(gRenderer, &screenRect);

// 		// Update the screen
// 		SDL_RenderPresent(gRenderer);

// 		j -= 5;
// 		// Wait for a short delay
// 		SDL_Delay(15);
// 	}
// 	return;
// }


bool Game::run( )
{
	Uint32 startTime = SDL_GetTicks();
	Uint32 gameDuration = 60; // 1 minutes
	Uint32 pauseStartTime = 0;
	Uint32 bullet_spawn_time = 2000;
	Uint32 last_decrease_time = startTime;

	GameState currentState = GAME;
	bool quit = false;
	SDL_Event e;

	int level = 2;

	Breakthrough breakthrough;
	HealSpell healspell(10, 2);

	breakthrough.createObject(100, 558, "character");

	auto character_iter = breakthrough.characters_list.begin();
	Ninja* ninja = dynamic_cast<Ninja*>(*character_iter);

	Uint32 current_time;
	Uint32 bullet_time = SDL_GetTicks();

	const Uint32 MS_PER_UPDATE = 50; //We can use this to separate the physics and animation speeds/updates 
	//but that would require restructuring the code and honestly that is too much work for now

	// if (character == SAMURAI){
	// 	assets = loadTexture("Assets/Samurai/Walk.png");
	// }
	// else if (character == SHINOBI){
	// 	assets = loadTexture("Assets/Shinobi/Walk.png");
	// }
	// else if (character == FIGHTER){
	// 	assets = loadTexture("Assets/Fighter/Walk.png");
	// }
	// assets = loadTexture("Assets/Samurai/Walk.png");

	// CharacterState currentState = WALKING;

	// char* fontpath = "FreeSans.ttf";
	// TTF_Init();
	// TTF_Font *Font = TTF_OpenFont(fontpath, 24);
	// Tower tower (gRenderer,"Assets/Backgrounds/OK.png",0,-23,378,637);
	Tower tower(gRenderer, "Assets/Backgrounds/OK.png", 900, 50, 378, 660);
	Cannon cannon1={Game::gRenderer, "Assets/cannon.png", 990, 540, 340*0.7, 278*0.7};
	// HealthBar healthbar(gRenderer, 1000, 180, 200, 200);
	Menu menu;
	if (!menu.init(gRenderer)) {
		printf("Failed to initialize Menu!\n");
	}
	std::string backgroundPath = "Assets/Backgrounds/Level" + std::to_string(level) + ".png";
	gTexture = loadTexture(backgroundPath);

	Uint32 last_health_decrease = tower.get_healthbar().get_current_health(); //200
	bool isPaused = false;
	while( !quit )
	{	
		Mix_VolumeMusic(menu.volume);
		if (menu.GameQuit){
			quit = true;
			return false;
		}
		if (menu.GameRestart){
			quit = true;
			return true;
		}
		//Handle events on queue
		ninja->isMoving = false;
		while( SDL_PollEvent( &e ) != 0 )
		{	
			mouseClick.handleEvent(e);
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
				return false;
			}
			if (menu.handleEvent(e)){
				currentState = MENU;
				isPaused = true;
				pauseStartTime = SDL_GetTicks();
			}
			else if (currentState == MENU && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            // The escape key was pressed while in the menu state, switch back to the gameplay state
				currentState = GAME;
				isPaused = false;
				startTime += SDL_GetTicks() - pauseStartTime;
				bullet_time += SDL_GetTicks() - pauseStartTime;
				pauseStartTime = 0;
        	}
			// if(e.type == SDL_MOUSEBUTTONDOWN){
			// //this is a good location to add pigeon in linked list.
			// 	if (e.button.button == SDL_BUTTON_LEFT)
			// 	{
			// 		int xMouse, yMouse;
			// 		SDL_GetMouseState(&xMouse,&yMouse);
			// 		// breakthrough.createObject(xMouse, yMouse, "character");
			// 		// level += 1;
			// 		// std::cout << "Level: " << level << std::endl;
			// 	}
			// }
		


			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_1 && healspell.get_num_uses() > 0)
				{
					healspell.effect(breakthrough.characters_list);
					healspell.reduce_uses();
				}

				else if (e.key.keysym.sym == SDLK_RIGHT or e.key.keysym.sym == SDLK_d)
				{
					// Move character if right arrow key is pressed
					std::cout << "right" << std::endl;
					ninja->isMoving = true;
					ninja->move();
				}

				else if (e.key.keysym.sym == SDLK_LEFT or e.key.keysym.sym == SDLK_a){
					ninja->isMoving = true;
					ninja->moveBack();
				}

				else if (e.key.keysym.sym == SDLK_UP or e.key.keysym.sym == SDLK_w)
				{
					// Move character if right arrow key is pressed
					ninja->jump();
				}

				else if (e.key.keysym.sym == SDLK_x)
				{
					// Move character if right arrow key is pressed
					std::cout << "attack" << std::endl;
					ninja->attack();
					ninja->isAttacking = true;
					if (ninja->get_mover().x >=760)
					{
						tower.get_healthbar().reduce_health(ninja->get_damage());
					}

				}


			}
		}

		
		if (ninja->isAttacking == true){
				std::cout << "attack" << std::endl;
				ninja->attack();
				if (ninja->get_mover().x >=760)
				{
					tower.get_healthbar().reduce_health(ninja->get_damage());
				}
				// if (ninja->AframeCount)
			}

		if (ninja->isJumping == true){
			ninja->jump();
			if (ninja->get_mover().y > 558)
			{
				ninja->isJumping = false;
			}
		}

		if (!ninja->isJumping && !ninja->isAttacking && !ninja->isMoving){
			ninja->idle();
		}

		if (!isPaused) {
			current_time = SDL_GetTicks();
		}
		SDL_RenderClear(gRenderer); //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
		tower.render();
		
		if (!isPaused && current_time - bullet_time >= bullet_spawn_time)
		{
			breakthrough.createObject(800, 400, "bullet");
			bullet_time = current_time;
		}
		//decrease bullet spawn time by 200ms every 10 seconds
		if (!isPaused && (current_time - last_decrease_time) >= 10000)
		{
			bullet_spawn_time -= 200;
			last_decrease_time = current_time;
		}
		if (!isPaused && last_health_decrease - tower.get_healthbar().get_current_health() >= 50)
		{
			bullet_spawn_time -= 100;
			last_health_decrease = tower.get_healthbar().get_current_health();
		}
		if (!isPaused){
		breakthrough.drawObjects();
		breakthrough.detect_collision();
		if (ninja->get_health().get_current_health() <= 0)
		{
			endGameScreen(false);
			quit = true;
		}
		if (tower.get_healthbar().get_current_health() <= 0)
		{	
			endGameScreen(true);
			quit = true;
		}
		}
		if (currentState == MENU){
			menu.renderMenuScreen(gRenderer, e);
			mouseClick.render(gRenderer);
			SDL_RenderPresent(gRenderer);
			SDL_Delay(10);
			continue;
		}


		if (!isPaused){
		// Calculate elapsed time in seconds
		Uint32 elapsedTime = (current_time - startTime) / 1000;

		// Create a string to display the timer
		std::string timerText = "Time: " + std::to_string(60-elapsedTime);

		// Render the timer text
		// You'll need to replace this with the actual code to render text in your game
		renderText(timerText, 600 , 20);

		// If the elapsed time is greater than the duration of your game, end the game
		if (elapsedTime > gameDuration) {
			quit = true;
			endGameScreen(false);
		}
		}

		cannon1.render();
		menu.render(gRenderer);
		mouseClick.render(gRenderer);
		// healthbar.render();

    	SDL_RenderPresent(gRenderer); //displays the updated renderer

	    SDL_Delay(15);	//causes sdl engine to delay for specified miliseconds
		//SDL_Delay can be lowered to 10-20 for smoother animation
	}

	if (gTexture != nullptr){
		SDL_DestroyTexture(gTexture);
		gTexture = nullptr;
	}

	return false;
			
}

void Game::renderText(const std::string& text, int x, int y) {
	// Load the font
	TTF_Font* font = TTF_OpenFont("Assets/Font.ttf", 24);
	if (font == nullptr) {
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
		return;
	}

	// Create a color for the text
	SDL_Color color = {255, 255, 255, 255};  // White color

	// Create a surface from the text
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == nullptr) {
		std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
		TTF_CloseFont(font);
		return;
	}

	// Create a texture from the surface
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	if (texture == nullptr) {
		std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
	}

	// Free the surface as it's no longer needed
	SDL_FreeSurface(surface);

	// Create a rectangle for the texture
	SDL_Rect dst = {x, y, surface->w, surface->h};

	// Render the texture
	SDL_RenderCopy(gRenderer, texture, nullptr, &dst);

	// Free the texture as it's no longer needed
	SDL_DestroyTexture(texture);

	// Close the font
	TTF_CloseFont(font);
}

void Game::endGameScreen(bool win){
	Mix_HaltMusic();
	
	// Open the font
	TTF_Font* font = TTF_OpenFont("Assets/Font.ttf", 70);
	SDL_Surface* textSurface = nullptr;

	Mix_Music* EndMusic = nullptr;
	// Create a surface from the text
	if (win){
		textSurface = TTF_RenderText_Solid(font, "You Win", SDL_Color{255, 255, 255, 255});
		//load lose music
		EndMusic = Mix_LoadMUS("Assets/End/win.mp3");
	}
	else{
		textSurface = TTF_RenderText_Solid(font, "You Lose", SDL_Color{255, 255, 255, 255});
		//load win music
		EndMusic = Mix_LoadMUS("Assets/End/lose.mp3");
	}
	//play music
	Mix_PlayMusic(EndMusic, 0);
	// Create a texture from the surface
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

	// Free the surface as it's no longer needed
	SDL_FreeSurface(textSurface);

	// Create a rectangle for the text texture
	SDL_Rect textDst = {SCREEN_WIDTH / 2 - textSurface->w / 2, SCREEN_HEIGHT / 2 - textSurface->h / 2, textSurface->w, textSurface->h};

	// Create an event variable
	SDL_Event e;

	// Wait for a click event
	bool isClicked = false;
	while (!isClicked) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				isClicked = true;
			} else if (e.type == SDL_MOUSEBUTTONDOWN) {
				isClicked = true;
			}
		}

		// Set the draw color to black
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

		// Clear the screen
		SDL_RenderClear(gRenderer);

		// Render the text texture
		SDL_RenderCopy(gRenderer, textTexture, NULL, &textDst);

		mouseClick.render(gRenderer);

		// Update the screen
		SDL_RenderPresent(gRenderer);
	}

	// Free the text texture as it's no longer needed
	SDL_DestroyTexture(textTexture);

	// Close the font
	TTF_CloseFont(font);

	// Make the credits music
	Mix_Music* creditsMusic = Mix_LoadMUS("Assets/Credits.mp3");

	//Play credits music
	Mix_PlayMusic(creditsMusic, -1);
	// Credits animation
	TTF_Font* creditsFont = TTF_OpenFont("Assets/Font.ttf", 30);
	std::vector<std::string> creditsTexts = {"Credits:", "Zohaib Aslam: The one who doesn't know how to 'commit'", "Ahsan Siddiqui: The one who did most of the work ;p", "Hassaan Tariq: Copilot cracker"};
	std::vector<SDL_Texture*> creditsTextures;
	std::vector<SDL_Rect> creditsRects;

	int y = SCREEN_HEIGHT;
	for (const auto& text : creditsTexts) {
		SDL_Surface* surface = TTF_RenderText_Solid(creditsFont, text.c_str(), SDL_Color{255, 255, 255, 255});
		SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
		SDL_Rect rect = {SCREEN_WIDTH / 2 - surface->w / 2, y, surface->w, surface->h};
		y += surface->h + 10;  // Add some space between lines

		creditsTextures.push_back(texture);
		creditsRects.push_back(rect);

		SDL_FreeSurface(surface);
	}

	while (creditsRects.back().y + creditsRects.back().h > 0) {
		
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT or e.type == SDL_MOUSEBUTTONDOWN) {
				for (auto& texture : creditsTextures) {
					SDL_DestroyTexture(texture);
				}
				TTF_CloseFont(creditsFont);
				return;
			}
		}

		for (size_t i = 0; i < creditsTextures.size(); ++i) {
			SDL_RenderCopy(gRenderer, creditsTextures[i], NULL, &creditsRects[i]);
			creditsRects[i].y -= 1;
		}

		mouseClick.render(gRenderer);
		SDL_RenderPresent(gRenderer);
		SDL_Delay(10);
	}

	for (auto& texture : creditsTextures) {
		SDL_DestroyTexture(texture);
	}
	Mix_FreeMusic(EndMusic);
	Mix_FreeMusic(creditsMusic);
	TTF_CloseFont(creditsFont);
}
	// Uint8 r, g, b, a;
	// SDL_GetRenderDrawColor(gRenderer, &r, &g, &b, &a);

	// // Assuming the tower's position is (towerX, towerY)
	// int towerX = 100, towerY = 100;

	// // Size of each frame
	// int frameWidth = 96, frameHeight = 96;

	// // Total number of frames in the sprite sheet
	// int totalFrames = 12;

	// // Current frame
	// int currentFrame = 0;

	// // Rectangle for source and destination
	// SDL_Rect srcRect, dstRect;

	// // Set the dimensions of the source rectangle
	// srcRect.x = currentFrame * frameWidth;
	// srcRect.y = 0;
	// srcRect.w = frameWidth;
	// srcRect.h = frameHeight;

	// // Set the dimensions of the destination rectangle
	// dstRect.x = towerX;
	// dstRect.y = towerY;
	// dstRect.w = frameWidth;
	// dstRect.h = frameHeight;

	// // Loop through each frame
	// for (int i = 0; i < totalFrames; i++) {
	// 	// Set the render draw color back to its original state
	// 	SDL_SetRenderDrawColor(gRenderer, r, g, b, a);

	// 	// Clear the renderer
	// 	SDL_RenderClear(gRenderer);

	// 	// Set the source rectangle x position to the current frame
	// 	srcRect.x = i * frameWidth;

	// 	// Render the current frame
	// 	SDL_RenderCopy(gRenderer, explosion, &srcRect, &dstRect);

	// 	// Update the screen
	// 	SDL_RenderPresent(gRenderer);

	// 	// Delay to control the speed of the animation
	// 	SDL_Delay(100);
	// }