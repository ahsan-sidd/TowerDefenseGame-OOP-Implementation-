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

void Ninja::draw(Unit* ptr)
{
    SDL_RenderCopy(Game::gRenderer, Game::assets, &ptr->get_src(), &ptr->get_mover());
    // std::cout << "health " << ch << " ";
    hb.render();
}

void Ninja::move(){
    //Attack when the sprite reaches x=850
    get_src().w = 128;
    get_src().h = 128;
    // get_mover().w = 128;
    // get_mover().h = 128;
    if (get_mover().x < 800)
    {
    if (WanimationDelay == 4){

	frameCount++;
	if (frameCount % 8 == 0){
		get_src().x = 0;
		get_src().y = 0;
	}
	else{
		get_src().x += 128;
	}
		// Character.srcRect.x += 128;
		WanimationDelay = 0;
	}
    get_mover().x += 7;
    hb.set_x(7);
	WanimationDelay++;}
    else{
        attack();
    }
}

void Ninja::attack()
{
    game.assets = game.loadTexture("Assets/Samurai/Attack_1.png");
    if (WanimationDelay == 3){

	frameCount++;
	if (frameCount % 5 == 0){
		get_src().x = 0;
		get_src().y = 0;
	}
	else{
		get_src().x += 128;
	}
		// Character.srcRect.x += 128;
		WanimationDelay = 0;
	}
    // get_mover().x += 10;
	WanimationDelay++;// if (attack_frame == 0)

}

    // src coorinates from assets.png file, they have been found using spritecow.com
Ninja::Ninja(SDL_Rect s, SDL_Rect m) : Unit(s, m), srcRect{s}, moverRect{m}, hb(Game::gRenderer, moverRect.x + 40, moverRect.y - 5, current_health, max_health){

}

HealthBar& Ninja::get_hb()
{
    return hb;
}

