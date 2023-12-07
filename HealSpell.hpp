#include "Spell.hpp"
#include <SDL.h>
#include <list>
#include "Unit.hpp"

class HealSpell : public Spell
{
public:
    HealSpell(int effect, int time);
    void effect(std::list<Unit*> characters_list);
};