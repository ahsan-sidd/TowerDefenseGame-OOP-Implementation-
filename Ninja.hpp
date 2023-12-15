#ifndef Ninja_HPP
#define Ninja_HPP

#include<SDL.h>
#include "game.hpp"
#include "HealthBar.hpp"
#include "Unit.hpp"
class Ninja : public Unit{

    SDL_Rect srcRect, moverRect;
    int movement_frame = 0;
    int movement_speed = 10;
    // int attack_frame = 0;
    int WanimationDelay = 0;
    int AanimationDelay = 0;
    int WframeCount = 0;
    int AframeCount = 0;
    int current_health = 50;
    int max_health = 50;
    int damage = 1;
    HealthBar hb;

public:
    // add the fly function here as well.
    ~Ninja();
    void draw(Unit* ptr);
    void move();
    void attack();
    int get_damage();
    Ninja(SDL_Rect s, SDL_Rect m);
    HealthBar& get_health();

    bool isAttacking = false;
    SDL_Texture* SamuraiWalkTexture = Game::loadTexture("Assets/Samurai/Walk.png");
    SDL_Texture* SamuraiAttackTexture = Game::loadTexture("Assets/Samurai/Attack_2.png");
    SDL_Texture* FighterWalkTexture = Game::loadTexture("Assets/Fighter/Walk.png");
    SDL_Texture* FighterAttackTexture = Game::loadTexture("Assets/Fighter/Attack_3.png");
    SDL_Texture* ShinobiWalkTexture = Game::loadTexture("Assets/Shinobi/Walk.png");
    SDL_Texture* ShinobiAttackTexture = Game::loadTexture("Assets/Shinobi/Attack_3.png");
    // may add other overloaded constructors here... 
};
#endif
