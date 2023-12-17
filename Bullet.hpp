#include<SDL.h>
#include "game.hpp"
#include "Unit.hpp"
class Bullet : public Unit{

    SDL_Rect srcRect, moverRect;
    SDL_Texture* bulletTexture;
    int movement_speed = 5;
    int damage = 5;


public:
    void draw(Unit* ptr);
    void move();
    void attack();
    Bullet(SDL_Rect s, SDL_Rect m, SDL_Texture* texture);
    int get_damage();
};
