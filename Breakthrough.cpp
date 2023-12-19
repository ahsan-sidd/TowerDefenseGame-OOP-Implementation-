#include <iostream>
#include "Breakthrough.hpp"
#include "ObjectCreator.hpp"
#include <string>
#include "Ninja.hpp"
#include "Bullet.hpp"
void Breakthrough::drawObjects()
{
    // call draw functions of all the objects here
    if (!characters_list.empty())
    {
        for (Unit* unit : characters_list) {
            unit->draw(unit);
        }
    }

    for (Unit* unit : bullets_list) {
        unit->draw(unit);
        unit->move();
        detect_collision();
    }
}

void Breakthrough::detect_collision()
{

    if (!characters_list.empty() && !bullets_list.empty())
    {
        for (auto bulletIter = bullets_list.begin(); bulletIter != bullets_list.end();)
        {
            auto firstCharacter = characters_list.begin();
            
            // check for collision, decrease health of character and remove bullet from screen and list if collision detected
            if ((*bulletIter)->get_mover().x < (*firstCharacter)->get_mover().x + 80 and (*bulletIter)->get_mover().x > (*firstCharacter)->get_mover().x + 20 and (*bulletIter)->get_mover().y < (*firstCharacter)->get_mover().y + 160 and (*bulletIter)->get_mover().y > (*firstCharacter)->get_mover().y)
            {
                Bullet* bullet = dynamic_cast<Bullet*>(*bulletIter);
                int damage = bullet->get_damage();

                (*firstCharacter)->get_health().reduce_health(damage);

                delete *bulletIter;
                *bulletIter = nullptr;
                bulletIter = bullets_list.erase(bulletIter);
            }
            else if (*bulletIter != nullptr and (*bulletIter)->get_mover().x < 0)
            {
                delete *bulletIter;
                *bulletIter = nullptr;
                bulletIter = bullets_list.erase(bulletIter);
            }

            // check for next bullet in the list
            else
            {
                bulletIter++;
            }
        }
    }
}



void Breakthrough::createObject(int x, int y, string object_to_create)
{

    ObjectCreator oc;
    Unit* ptr = oc.getObject(x, y, object_to_create);
    if (object_to_create == "character")
    {
        characters_list.push_back(ptr);
    }
    else if (object_to_create == "bullet")
    {
        bullets_list.push_back(ptr);   
    }
}

Breakthrough::~Breakthrough()
{
    for (Unit* unit : characters_list) {
        delete unit;
    }
    characters_list.clear();
    std::cout << "size of bullet list: " << bullets_list.size();
}
