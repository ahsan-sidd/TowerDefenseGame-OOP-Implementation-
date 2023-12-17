#include "Bullet.hpp"
#include <iostream>
#include "game.hpp"

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
}

int Bullet::get_damage()
{
    return damage;
}



void Bullet::set_damage()
{
    damage += 5;
}

int Bullet::damage = 5;