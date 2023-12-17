#include "Menu.hpp"

Menu::Menu() {
    // Initialize the MenuButtonRect to the desired position and size
    MenuButtonRect.x = 50; // Set this to the desired x position
    MenuButtonRect.y = 50; // Set this to the desired y position
    MenuButtonRect.w = 90; // Set this to the width of the button
    MenuButtonRect.h = 90; // Set this to the height of the button
}

Menu::~Menu() {
    // Free the texture
    if (MenuNormalButtonTexture != NULL) {
        SDL_DestroyTexture(MenuHoverButtonTexture);
        SDL_DestroyTexture(MenuNormalButtonTexture);
        MenuButtonTexture = NULL;
    }
}

bool Menu::init(SDL_Renderer* gRenderer) {
    // Load the button texture
    MenuNormalButtonTexture = loadTexture(gRenderer, "Assets/Menu/MenuButton.png");
    if (MenuNormalButtonTexture == NULL) {
        return false;
    }

    MenuHoverButtonTexture = loadTexture(gRenderer, "Assets/Menu/MenuButtonHover.png");
    if (MenuHoverButtonTexture == NULL) {
        return false;
    }

    // Get the dimensions of the texture and set the button rect to the same size
    SDL_QueryTexture(MenuButtonTexture, NULL, NULL, &MenuButtonRect.w, &MenuButtonRect.h);

    return true;
}

bool Menu::handleEvent(SDL_Event& e) {
    SDL_Point mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    if (SDL_PointInRect(&mousePos, &MenuButtonRect)) {
        // The mouse is over the button
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            // The button was clicked
            return true;

        } else if (e.type == SDL_MOUSEMOTION) {
            // The mouse moved over the button, change to the hover texture
            MenuButtonTexture = MenuHoverButtonTexture;
            // return true;
        }
    } else {
        // The mouse is not over the button, change back to the normal texture
        MenuButtonTexture = MenuNormalButtonTexture;
    }
    return false;
}

void Menu::render(SDL_Renderer* gRenderer) {
    // Render the button
    SDL_RenderCopy(gRenderer, MenuButtonTexture, NULL, &MenuButtonRect);
}

void Menu::renderMenuScreen(SDL_Renderer* gRenderer, SDL_Event& e) {
    SDL_Rect MenuRect = {422, 150, 400, 400};
    SDL_Texture* MenuTexture = loadTexture(gRenderer, "Assets/Menu/Menu.png");
    SDL_Rect QuitRect = {559,450, 126, 70};
    SDL_Texture* QuitTexture = loadTexture(gRenderer, "Assets/Menu/Quit.png");
    SDL_Texture* QuitHoverTexture = loadTexture(gRenderer, "Assets/Menu/QuitHover.png");
    SDL_Rect RestartRect = {516, 360, 212, 76};
    SDL_Texture* RestartTexture = loadTexture(gRenderer, "Assets/Menu/Restart.png");
    SDL_Texture* RestartHoverTexture = loadTexture(gRenderer, "Assets/Menu/RestartHover.png");
    
    SDL_Texture* SliderTexture = loadTexture(gRenderer, "Assets/Menu/Slider.png");

    
    SDL_RenderCopy(gRenderer, MenuTexture, NULL, &MenuRect);

    SDL_Point mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    if (SDL_PointInRect(&mousePos, &QuitRect)){
        SDL_RenderCopy(gRenderer, QuitHoverTexture, NULL, &QuitRect);
        }
    else{
        SDL_RenderCopy(gRenderer, QuitTexture, NULL, &QuitRect);
    }
    if (SDL_PointInRect(&mousePos, &RestartRect)){
        SDL_RenderCopy(gRenderer, RestartHoverTexture, NULL, &RestartRect);
    }
    else{
        SDL_RenderCopy(gRenderer, RestartTexture, NULL, &RestartRect);
    }
    // The x position of the slider when the mouse started dragging
    if (e.type == SDL_MOUSEBUTTONDOWN && SDL_PointInRect(&mousePos, &sliderRect)) {
        // The mouse clicked on the slider, start dragging
        isDragging = true;
    } else if (e.type == SDL_MOUSEBUTTONUP) {
        // The mouse button was released, stop dragging
        isDragging = false;
    } else if (e.type == SDL_MOUSEMOTION && isDragging) {
        // The mouse moved while dragging, update the slider position
        sliderRect.x = std::max(sliderStartX, std::min(sliderEndX, mousePos.x));
        volume = (sliderRect.x - sliderStartX) / (float)(sliderEndX - sliderStartX) * MIX_MAX_VOLUME;
        std::cout << "Volume: " << volume << std::endl;
        // Mix_Volume(-1, volume);
    }
    if (e.type == SDL_MOUSEBUTTONDOWN && SDL_PointInRect(&mousePos, &QuitRect)){
        GameQuit = true;
    }
    if (e.type == SDL_MOUSEBUTTONDOWN && SDL_PointInRect(&mousePos, &RestartRect)){
        GameRestart = true;
    }
    

    SDL_RenderCopy(gRenderer, SliderTexture, NULL, &sliderRect);
    
    SDL_DestroyTexture(RestartTexture);
    SDL_DestroyTexture(MenuTexture);
    SDL_DestroyTexture(QuitTexture);
    SDL_DestroyTexture(RestartHoverTexture);
    SDL_DestroyTexture(QuitHoverTexture);
    SDL_DestroyTexture(SliderTexture);
}

SDL_Texture* Menu::loadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}