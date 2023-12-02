#include "HealthBar.hpp"
#include <SDL.h>
HealthBar::HealthBar(){}
HealthBar::HealthBar(SDL_Renderer* new_renderer, int new_x, int new_y, int curr_health, int new_max_health)
: renderer{new_renderer}, x{new_x}, y(new_y), max_health{new_max_health}, current_health{curr_health}
{
}
HealthBar::~HealthBar()
{

}
void HealthBar::reduce_health(int damage)
{
    current_health -= damage;
    if (current_health < 0)
    {
        current_health = 0;
    }
}

void HealthBar::render()
{
    // Draw background rectangle (healthbar) of white color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect bg_healthbar = {x, y, max_health, 10};
    SDL_RenderFillRect(renderer, &bg_healthbar);

    // Draw a green rectangle represnting health, inside / on top of the background of healthbar
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect healthbar = {x, y, current_health, 10};
    SDL_RenderFillRect(renderer, &healthbar);
}

void HealthBar::set_x(int value)
{
    x += value;
}