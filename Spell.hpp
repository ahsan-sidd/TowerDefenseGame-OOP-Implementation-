#ifndef SPELL_HPP
#define SPELL_HPP

#include <SDL.h>
#include <list>
#include "Unit.hpp"

class Spell {
protected:
    int effect_amount;
    int duration;
    int num_uses;

public:
    virtual void effect(std::list<Unit*> characters_list) {};
    Spell(int effect, int time);
    int get_num_uses();
    void reduce_uses();
    void increase_uses();
};

#endif
