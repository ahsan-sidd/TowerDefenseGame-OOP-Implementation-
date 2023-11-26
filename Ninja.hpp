#include<SDL.h>
#include "game.hpp"
#include "Unit.hpp"
class Ninja : public Unit{

    // SDL_Rect srcRect, moverRect;
    int movement_frame = 0;
    int movement_speed = 10;
    int attack_frame = 0;

public:
    // add the fly function here as well.
    // void draw();
    void move();
    void attack();
    Ninja(SDL_Rect s, SDL_Rect m); 
    // may add other overloaded constructors here... 
};
