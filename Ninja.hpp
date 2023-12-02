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
    int frameCount = 0;
    int current_health = 50;
    int max_health = 50;
    HealthBar hb;

public:
    // add the fly function here as well.
    void draw(Unit* ptr);
    void move();
    void attack();
    Ninja(SDL_Rect s, SDL_Rect m); 
    // may add other overloaded constructors here... 
};
#endif
