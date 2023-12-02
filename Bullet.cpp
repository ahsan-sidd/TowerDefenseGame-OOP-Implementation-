#include "Bullet.hpp"
#include <iostream>
#include "game.hpp"
// pigeon implementation will go here.


// in project implementation this draw function should only be in superclass
// void Pigeon::draw(){
//     SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
// }


// fly() is overrided from the superclass

void Bullet::draw(Unit* ptr)
{
    SDL_RenderCopy(Game::gRenderer, bulletTexture, &ptr->get_src(), &ptr->get_mover());
}

void Bullet::move()
{
    get_mover().x -= movement_speed;
}

void Bullet::attack()
{

}

Bullet::Bullet(SDL_Rect s, SDL_Rect m, SDL_Texture* texture) : Unit(s, m){
    srcRect = s;
    moverRect = m;
    bulletTexture = texture;
    // srcRect = {7,88,160,103};

    // it will display pigeon on x = 30, y = 40 location, the size of pigeon is 50 width, 60 height
    // moverRect = {30, 40, 50, 50};
}

int Bullet::get_damage()
{
    return damage;
}