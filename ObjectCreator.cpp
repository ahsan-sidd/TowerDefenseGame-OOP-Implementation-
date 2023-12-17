#include <SDL.h>
#include "ObjectCreator.hpp"
#include "Ninja.hpp"
#include <iostream>
#include <string>
#include "Bullet.hpp"

SDL_Texture* ObjectCreator::loadTexture(SDL_Renderer* renderer, std::string path)
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
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

Unit* ObjectCreator::getObject(int new_x, int new_y, std::string object_to_create)
{
    if (object_to_create == "character")
    {
        int random = rand() % 3;
        if (random == 0 || random == 1 || random == 2)
        {
            return new Ninja({0, 0, 128, 128}, {new_x, 558, 160, 160});
        }
    }
    else if (object_to_create == "bullet")
    {
        SDL_Texture* bullet_texture = loadTexture(Game::gRenderer, "Assets/blackball.png");
        return new Bullet({241, 57, 241, 245}, {1100, 612, 30, 30}, bullet_texture);
    }
}