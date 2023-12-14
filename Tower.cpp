
#include "Tower.hpp"
#include "Game.hpp" // Include Game.hpp or any other necessary headers for loadTexture function

Tower::Tower(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height)
    : gRenderer(renderer) {
    // Load tower texture
    towerTexture = Game::loadTexture(imagePath);
    healthbar={gRenderer, 1000, 180, 200, 200};
    // Set tower properties
    towerRect = { x, y, width, height };
    cannon1={gRenderer, "Assets/cannon.png", 1000, 180, 200, 200};
}
Tower::~Tower() {
    // Free tower texture when the object is destroyed
    SDL_DestroyTexture(towerTexture);
}

void Tower::render() {
    // Render the tower
    SDL_RenderCopy(gRenderer, towerTexture, NULL, &towerRect);
    cannon1.render();
    healthbar.render();
}

