#include "game.hpp"
#include "Ninja.hpp"
#include <iostream>
#include "HealthBar.hpp"

Game game;

Ninja::~Ninja(){
	SDL_DestroyTexture(SamuraiWalkTexture);
	SDL_DestroyTexture(SamuraiAttackTexture);
	SDL_DestroyTexture(FighterWalkTexture);
	SDL_DestroyTexture(FighterAttackTexture);
	SDL_DestroyTexture(ShinobiWalkTexture);
	SDL_DestroyTexture(ShinobiAttackTexture);
}

void Ninja::move() {
	static Uint32 lastUpdate = SDL_GetTicks(); // Time of last animation frame update
	Uint32 current = SDL_GetTicks(); // Current time

	if (get_mover().x < 800) {
		if (current - lastUpdate >= 100) { // Change the frame every 100ms
			WframeCount = (WframeCount + 1) % 8; // Keep frameCount between 0 and 7
			get_src().x = WframeCount * 128; // Update the x position in the source rectangle
			lastUpdate = current; // Update the time of last animation frame update
		}
		get_mover().x += 7; // Increase the x position to move right
		hb.set_x(7); // Update the health bar position
		isMoving = true;
		isAttacking = false; // The Ninja is not attacking
	}
}

void Ninja::moveBack() {
	if (get_mover().x > 0) {  // Check if the Ninja is not at the left edge of the screen
		WanimationDelay++;
		if (WanimationDelay == 10000) {  // Change the frame every 134 calls to this function
			WframeCount = (WframeCount + 1) % 8;  // Keep frameCount between 0 and 7
			get_src().x = WframeCount * 128;  // Update the x position in the source rectangle
			WanimationDelay = 0;  // Reset the delay counter
		}
		get_mover().x -= 7;  // Decrease the x position to move left
		hb.set_x(-7);  // Update the health bar position
		isMoving = true;
		isAttacking = false;  // The Ninja is not attacking
	}
}

void Ninja::draw(Unit* ptr)
{
	SDL_Texture* texture;
	if (isJumping){
		switch (Game::character) {
			case SAMURAI:
				texture = SamuraiJumpTexture;
				break;
			case SHINOBI:
				texture = ShinobiJumpTexture;
				break;
			case FIGHTER:
				texture = FighterJumpTexture;
				break;
			default:
				texture = Game::assets;  // Default to the original texture
				break;
		}
	}
	else if (isAttacking) {
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
	} else if (isMoving) {
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
	} else {
		switch (Game::character) {
			case SAMURAI:
				texture = SamuraiIdleTexture;
				break;
			case SHINOBI:
				texture = ShinobiIdleTexture;
				break;
			case FIGHTER:
				texture = FighterIdleTexture;
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
	if (!isAttacking) {
		isAttacking = true;
		// AframeCount = 0;
	}
	if (AanimationDelay == 5){
		AframeCount = (AframeCount + 1) % 4;  // Keep frameCount between 0 and 3
		if (AframeCount == 0){
			get_src().x = 0;
			// get_src().y = 0;
		}
		else{
			get_src().x += 128;
		}
		AanimationDelay = 0;
	}
	else {
		AanimationDelay++;
	}
	if (AframeCount == 3){
		isAttacking = false;
		// frameCount = 0;
	}
}

void Ninja::jump(){
	if (!isJumping) {
		isJumping = true;
		JframeCount = 0;
		yVelocity = -20;  // Initial upward velocity
	}

	if (yVelocity < 20) {  // Limit the downward velocity to 20
		yVelocity += 1;  // Gravity effect
	}

	get_mover().y += yVelocity;  // Apply the velocity to the y position
	hb.set_y(yVelocity);  // Update the health bar position

	if (JanimationDelay == 5){
		JanimationDelay = 0;
		if (JframeCount == 0){
			get_src().x = 0;
		}
		else{
			get_src().x += 128;
		}

		JframeCount = (JframeCount + 1) % 10;  // Keep frameCount between 0 and 9
	}
	else {
		JanimationDelay++;
	}
	if (get_mover().y >= 558){  // Check if the Ninja has reached the ground
		get_mover().y = 558;
		isJumping = false;
		yVelocity = 0;  // Reset the velocity so the Ninja doesn't continue to move downwards
	}
}

void Ninja::idle(){
	WframeCount = (WframeCount + 1) % 6;  // Keep frameCount between 0 and 7
	if (WframeCount == 0){
		get_src().x = 0;
		// get_src().y = 0;
	}
	else{
		get_src().x += 128;
	}
}

    // src coorinates from assets.png file, they have been found using spritecow.com
Ninja::Ninja(SDL_Rect s, SDL_Rect m) : Unit(s, m), srcRect{s}, moverRect{m}, hb(Game::gRenderer, moverRect.x + 40, moverRect.y - 5, current_health, max_health){

}

HealthBar& Ninja::get_health()
{
    return hb;
}

int Ninja::get_damage()
{
	return damage;
}

