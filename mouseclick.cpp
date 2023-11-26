#include "MouseClick.hpp"

MouseClick::MouseClick(){
    // Load click sound
    bool success = true;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
    }
    clickSound = Mix_LoadWAV("Assets/click.mp3");
    if (clickSound == nullptr) {
        printf("Failed to load click sound! SDL_mixer Error: %s\n", Mix_GetError());
    }
    
    cursorRect.x = 0;
    cursorRect.y = 0;
    cursorRect.w = 51; // Adjust to your cursor texture width
    cursorRect.h = 50; // Adjust to your cursor texture height
}

bool MouseClick::init(SDL_Renderer* renderer) {
    if (renderer == nullptr) {
        printf("Renderer is null! Cannot initialize MouseClick.\n");
        return false;
    }

    // this->renderer = renderer;

    cursorTexture = loadTexture(renderer, "Assets/Cursor.png"); // Replace with your cursor texture path
    
    if (cursorTexture == nullptr) {
        printf("Failed to load cursor texture! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

MouseClick::~MouseClick() {
    // Free click sound
    Mix_FreeChunk(clickSound);
    if (cursorTexture != nullptr){
        SDL_DestroyTexture(cursorTexture);
    }
    // SDL_DestroyTexture(cursorTexture);
}

void MouseClick::handleEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        // Get the mouse position
        int xMouse, yMouse;
        SDL_GetMouseState(&xMouse, &yMouse);

        // Check if the click is within the game screen
        if (xMouse >= 0 && xMouse < SCREEN_WIDTH && yMouse >= 0 && yMouse < SCREEN_HEIGHT) {
            playClickSound();
            // Add any other logic you want to execute on mouse click
        }
    }
}

void MouseClick::playClickSound() {
    // Play the click sound
    int channel = Mix_PlayChannel(-1, clickSound, 0);
    Mix_Volume(channel, 128);
}

void MouseClick::render(SDL_Renderer* renderer) {
    // Get the current mouse position
    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse, &yMouse);

    // std::cout << "cursorRect: " << cursorRect.w << cursorRect.h << std::endl;

    // Update the cursor position
    cursorRect.x = xMouse;
    cursorRect.y = yMouse;
    // cursorRect = {xMouse, yMouse, 51, 50};

    // Render the cursor
    SDL_RenderCopy(renderer, cursorTexture, NULL, &cursorRect);
}

SDL_Texture* MouseClick::loadTexture(SDL_Renderer* renderer ,const std::string& path) {
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
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}