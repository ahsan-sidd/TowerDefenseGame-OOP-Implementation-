#ifndef UNIT_HPP
#define UNIT_HPP
#include <SDL.h>
#include "HealthBar.hpp"
class Unit
{
private:
    SDL_Rect srcRect;
    SDL_Rect moverRect;
    int movement_speed;
public:
    Unit(SDL_Rect new_srcRect, SDL_Rect new_moverRect);
    virtual void draw(Unit* ptr) = 0;
    virtual void move() = 0;
    virtual void attack() = 0;
    virtual int get_damage() = 0;
    // virtual bool hasHealthBar();
    virtual HealthBar& get_health() {};

    SDL_Rect& get_src();
    SDL_Rect& get_mover();
};
#endif