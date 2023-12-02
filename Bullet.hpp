#include<SDL.h>
#include "game.hpp"
#include "Unit.hpp"
class Bullet : public Unit{

    SDL_Rect srcRect, moverRect;
    SDL_Texture* bulletTexture;
    int movement_frame = 0;
    int movement_speed = 10;

public:
    // add the fly function here as well.
    void draw(Unit* ptr);
    void move();
    void attack();
    Bullet(SDL_Rect s, SDL_Rect m, SDL_Texture* texture);
    // may add other overloaded constructors here... 
};
