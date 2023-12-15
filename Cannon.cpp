#include "Cannon.hpp"
#include "Game.hpp"
Cannon::Cannon(){}
Cannon::Cannon(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height)
    : cannonTexture(nullptr) {
    // Load cannon texture and set initial position
    cannonTexture = Game::loadTexture(imagePath);
    cannonRect = { x, y, width, height };
}

Cannon::~Cannon() {
    // Free resources
    SDL_DestroyTexture(cannonTexture);
}

void Cannon::render() {
    // Render the cannon
    // SDL_Rect cannonSrc = {0, 0, 308, 75};
    SDL_RenderCopy(Game::gRenderer, cannonTexture, NULL, &cannonRect);
}