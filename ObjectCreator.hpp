#include <SDL.h>
#include "Unit.hpp"
#include <string>
// #include <vector>

class ObjectCreator
{
private:
    int x;
    int y;
    // std::vector<Unit*> object_list;
public:
    SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path);
    Unit* getObject(int new_x, int new_y, std::string object_to_create);
};