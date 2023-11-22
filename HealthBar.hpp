#include<SDL.h>
#include "game.hpp"

class HealthBar
{
private:
    SDL_Renderer* renderer;
    int x;
    int y;
    int current_health;
    int max_health;

public:
    HealthBar(SDL_Renderer* renderer, int new_x, int new_y, int curr_health, int new_max_health);
    ~HealthBar();
    void render();
    void reduce_health();
};