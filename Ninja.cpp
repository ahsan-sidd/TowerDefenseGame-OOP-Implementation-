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
    if (get_mover().x < 850)
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
    // {
    //     get_src().x = 151;      
    //     get_src().y = 53;
    //     get_src().w = 100;
    //     get_src().h = 75;
    // }
    // else if (attack_frame == 1)
    // {
    //     get_src().x = 280;      
    //     get_src().y = 53;
    //     get_src().w = 101;
    //     get_src().h = 75;
    // }
    // else if (attack_frame == 2)
    // {
    //     get_src().x = 23;      
    //     get_src().y = 53;
    //     get_src().w = 79;
    //     get_src().h = 75;
    //     attack_frame = 0;
    // }
    // attack_frame++;
    // SDL_Delay(500);
}

    // src coorinates from assets.png file, they have been found using spritecow.com
Ninja::Ninja(SDL_Rect s, SDL_Rect m) : Unit(s, m), srcRect{s}, moverRect{m}, hb(Game::gRenderer, moverRect.x + 40, moverRect.y - 5, current_health, max_health){
    // srcRect = s;
    // moverRect = m;
    // srcRect = {7,88,160,103};

    // it will display pigeon on x = 30, y = 40 location, the size of pigeon is 50 width, 60 height
    // moverRect = {30, 40, 50, 50};
}

HealthBar& Ninja::get_hb()
{
    return hb;
}

