#ifndef HealthBar_HPP
#define HealthBar_HPP

#include<SDL.h>
// #include "game.hpp"

class HealthBar
{
private:
    SDL_Renderer* renderer;
    int x;
    int y;
    int current_health;
    int max_health;

public:
    HealthBar() {};
    HealthBar(SDL_Renderer* renderer, int new_x, int new_y, int curr_health, int new_max_health);
    ~HealthBar();
    void render();
    void reduce_health(int damage);
    int get_current_health();
    void set_x(int value);
    void set_current_health(int amount);
};
#endif