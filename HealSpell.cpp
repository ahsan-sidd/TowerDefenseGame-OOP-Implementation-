#include "HealSpell.hpp"
#include "Breakthrough.hpp"

HealSpell::HealSpell(int effect, int time)
: Spell(effect, time)
{
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