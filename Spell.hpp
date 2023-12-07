#ifndef SPELL_HPP
#define SPELL_HPP

#include <SDL.h>
#include <list>
#include "Unit.hpp"

class Spell {
protected:
    int effect_amount;
    int duration;

public:
    virtual void effect(std::list<Unit*> characters_list) {};
    Spell(int effect, int time);
};

#endif
