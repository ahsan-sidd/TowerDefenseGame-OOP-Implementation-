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

Ninja::~Ninja(){
	SDL_DestroyTexture(SamuraiWalkTexture);
	SDL_DestroyTexture(SamuraiAttackTexture);
	SDL_DestroyTexture(FighterWalkTexture);
	SDL_DestroyTexture(FighterAttackTexture);
	SDL_DestroyTexture(ShinobiWalkTexture);
	SDL_DestroyTexture(ShinobiAttackTexture);
}

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
	SDL_Texture* texture;
	if (isAttacking) {
		switch (Game::character) {
			case SAMURAI:
				texture = SamuraiAttackTexture;
				break;
			case SHINOBI:
				texture = ShinobiAttackTexture;
				break;
			case FIGHTER:
				texture = FighterAttackTexture;
				break;
			default:
				texture = Game::assets;  // Default to the original texture
				break;
		}
	} else {
		switch (Game::character) {
			case SAMURAI:
				texture = SamuraiWalkTexture;
				break;
			case SHINOBI:
				texture = ShinobiWalkTexture;
				break;
			case FIGHTER:
				texture = FighterWalkTexture;
				break;
			default:
				texture = Game::assets;  // Default to the original texture
				break;
		}
	}
	SDL_RenderCopy(Game::gRenderer, texture, &ptr->get_src(), &ptr->get_mover());
	hb.render();
}

void Ninja::attack()
{
	// game.assets = attackTexture;
	if (AanimationDelay == 3){
		frameCount = (frameCount + 1) % 4;  // Keep frameCount between 0 and 3
		if (frameCount == 0){
			get_src().x = 0;
			get_src().y = 0;
		}
		else{
			get_src().x += 128;
		}
		AanimationDelay = 0;
	}
	else {
		AanimationDelay++;
	}
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

int Ninja::get_damage()
{
	return damage;
}

