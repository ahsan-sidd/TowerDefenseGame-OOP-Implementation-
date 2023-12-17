#include "Spell.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include "Unit.hpp"

class HealSpell : public Spell
{
public:
    HealSpell(int effect, int time);
    ~HealSpell();
    void effect(std::list<Unit*> characters_list);
    void increase_bullet_damage();

};