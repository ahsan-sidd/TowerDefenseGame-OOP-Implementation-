#include "game.hpp"
#include "Ninja.hpp"
#include <iostream>
#include "HealthBar.hpp"
// pigeon implementation will go here.


// in project implementation this draw function should only be in superclass
// void Pigeon::draw(){
//     SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
// }


// fly() is overrided from the superclass
Game game;
// Add a new property to the Ninja class to track whether it's attacking or not


void Ninja::move(){
	// int attackDistance = 50;
	if (get_mover().x < 800)
	{
		if (WanimationDelay == 4){
			frameCount = (frameCount + 1) % 8;  // Keep frameCount between 0 and 7
			if (frameCount == 0){
				get_src().x = 0;
				get_src().y = 0;
			}
			else{
				get_src().x += 128;
			}
			WanimationDelay = 0;
		}
		get_mover().x += 7;
		hb.set_x(7);
		WanimationDelay++;
		isAttacking = false;  // The Ninja is not attacking
	}
	else{
		attack();
		isAttacking = true;  // The Ninja is attacking
	}
}

void Ninja::draw(Unit* ptr)
{
	// Choose the appropriate texture based on whether the Ninja is attacking or not
	SDL_Texture* texture = isAttacking ? attackTexture : Game::assets;
	SDL_RenderCopy(Game::gRenderer, texture, &ptr->get_src(), &ptr->get_mover());
	hb.render();
}

void Ninja::attack()
{
    // game.assets = attackTexture;
    if (WanimationDelay == 3){
        frameCount = (frameCount + 1) % 5;  // Keep frameCount between 0 and 4
        if (frameCount == 0){
            get_src().x = 0;
            get_src().y = 0;
        }
        else{
            get_src().x += 128;
        }
        WanimationDelay = 0;
	}
    // get_mover().x += 10;
	WanimationDelay++;// if (attack_frame == 0)

}

    // src coorinates from assets.png file, they have been found using spritecow.com
Ninja::Ninja(SDL_Rect s, SDL_Rect m) : Unit(s, m), srcRect{s}, moverRect{m}, hb(Game::gRenderer, moverRect.x + 40, moverRect.y - 5, current_health, max_health){

}

// bool Ninja::hasHealthBar()
// {
//     return true;
// }

HealthBar& Ninja::get_health()
{
    return hb;
}

