#include <SDL.h>
#include "Unit.hpp"
#include "Breakthrough.hpp"
#include "game.hpp"


Unit::Unit(SDL_Rect new_srcRect, SDL_Rect new_moverRect)
: srcRect{new_srcRect}, moverRect{new_moverRect}
{
}

SDL_Rect& Unit::get_src()
{
    return srcRect;
}
SDL_Rect& Unit::get_mover()
{
    return moverRect;
}