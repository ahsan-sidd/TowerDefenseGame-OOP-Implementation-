#include "HealSpell.hpp"
#include "Breakthrough.hpp"
#include <iostream>

HealSpell::HealSpell(int effect, int time)
: Spell(effect, time)
{
    // SDL_Surface* iconSurfaceAvailable = IMG_Load("heal.png");
    // iconAvailable = SDL_CreateTextureFromSurface(gRenderer, iconSurfaceAvailable);
    // SDL_FreeSurface(iconSurfaceAvailable);
    // if (iconAvailable == nullptr)
    // {
    //     std::cout << "Error: " << SDL_GetError() << std::endl;
    // }

    // SDL_Surface* iconSurfaceUnavailable = IMG_Load("emptyHeal.png");
    // iconUnavailable = SDL_CreateTextureFromSurface(gRenderer, iconSurfaceUnavailable);
    // SDL_FreeSurface(iconSurfaceUnavailable);
    // if (iconUnavailable == nullptr)
    // {
    //     std::cout << "Error: " << SDL_GetError() << std::endl;
    // }
}

HealSpell::~HealSpell()
{
    // SDL_DestroyTexture(iconAvailable);
    // SDL_DestroyTexture(iconUnavailable);
}


void HealSpell::effect(std::list<Unit*> characters_list)
{
    auto firstCharacter = characters_list.begin();
    // Uint32 startTime = SDL_GetTicks();
    // while ((SDL_GetTicks() - startTime) < (duration * 1000))
    // {
    //     if ((SDL_GetTicks() - startTime) % 1000 == 0)
    //     {
    //         (*firstCharacter)->get_health().set_current_health(effect_amount);
    //     }
    // }
    int count = 0;
    while (count < duration)
    {
        (*firstCharacter)->get_health().set_current_health(effect_amount);
        count++;
    }

}