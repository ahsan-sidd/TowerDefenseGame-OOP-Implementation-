#include <SDL.h>
#include "Unit.hpp"
#include "Breakthrough.hpp"
#include "game.hpp"


Unit::Unit(SDL_Rect new_srcRect, SDL_Rect new_moverRect)
: srcRect{new_srcRect}, moverRect{new_moverRect}
{
}

// void Unit::draw(Unit* ptr)
// {
//     SDL_RenderCopy(Game::gRenderer, Game::assets, &ptr->srcRect, &ptr->moverRect);
//     // SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
// }
SDL_Rect& Unit::get_src()
{
    return srcRect;
}
SDL_Rect& Unit::get_mover()
{
    return moverRect;
}

// bool Unit::hasHealthBar()
// {
//     return false;
// }