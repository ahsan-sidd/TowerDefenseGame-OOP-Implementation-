#ifndef CANNON_HPP
#define CANNON_HPP

#include <SDL.h>
#include <string>

class Cannon {
public:
    Cannon();
    Cannon(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height);
    ~Cannon();

    void render();

private:
    // SDL_Renderer* gRenderer;
    SDL_Texture* cannonTexture;
    SDL_Rect cannonRect;
};

#endif // CANNON_HPP