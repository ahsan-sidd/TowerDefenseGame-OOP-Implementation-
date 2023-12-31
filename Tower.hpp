// Tower.hpp
#ifndef TOWER_HPP
#define TOWER_HPP

#include <SDL.h>
#include <string>
#include"HealthBar.hpp"
#include"Cannon.hpp"

class Tower {
public:
    Tower(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height);
    ~Tower();
    void render();
    HealthBar& get_healthbar();
private:
    // SDL_Renderer* gRenderer;
    SDL_Texture* towerTexture;
    SDL_Rect towerRect;
    HealthBar healthbar;
    Cannon cannon1;
};

#endif // TOWER_HPP
