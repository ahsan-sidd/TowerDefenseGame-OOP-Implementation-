#include "Spell.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include "Unit.hpp"

class HealSpell : public Spell
{
public:
    // SDL_Texture* iconAvailable = nullptr;
    // SDL_Texture* iconUnavailable = nullptr;
    HealSpell(int effect, int time);
    ~HealSpell();
    // HealSpell(int effect, int time, SDL_Renderer* renderer);
    void effect(std::list<Unit*> characters_list);
};