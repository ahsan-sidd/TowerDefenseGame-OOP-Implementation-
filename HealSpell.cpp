#include "HealSpell.hpp"
#include "Breakthrough.hpp"
#include <iostream>
#include "Bullet.hpp"

HealSpell::HealSpell(int effect, int time)
: Spell(effect, time)
{
}

HealSpell::~HealSpell()
{
}


void HealSpell::effect(std::list<Unit*> characters_list)
{
    auto firstCharacter = characters_list.begin();
    int count = 0;
    while (count < duration)
    {
        (*firstCharacter)->get_health().set_current_health(effect_amount);
        count++;
    }

}

void HealSpell::increase_bullet_damage() {
    Bullet::set_damage();
}