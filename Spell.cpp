#include "Spell.hpp"

Spell::Spell(int effect, int time)
: effect_amount{effect}, duration{time}, num_uses{1}
{
}

int Spell::get_num_uses()
{
    return num_uses;
}

void Spell::reduce_uses()
{
    num_uses--;
}