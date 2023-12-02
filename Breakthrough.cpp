#include <iostream>
#include "Breakthrough.hpp"
#include "ObjectCreator.hpp"
#include <string>
void Breakthrough::drawObjects()
{
    // call draw functions of all the objects here
    for (Unit* unit : characters_list) {
        unit->draw(unit);
        unit->move();
    }

    for (Unit* unit : bullets_list) {
        unit->draw(unit);
        unit->move();
        detect_collision();
    }
}

void Breakthrough::detect_collision()
{
    // if (!characters_list.empty() && !bullets_list.empty())
    // {
    //     for (Unit* unit : bullets_list)
    //     {
    //         if (unit->get_mover().x < characters_list.front()->get_mover().x)
    //         {
    //             cout << "collision ";
    //         }
    //     }
    // }

    if (!characters_list.empty() && !bullets_list.empty())
    {
        for (auto bulletIter = bullets_list.begin(); bulletIter != bullets_list.end();)
        {
            auto firstCharacter = characters_list.begin();
            
            // check for collision and remove bullet from screen and list if collision detected
            if ((*bulletIter)->get_mover().x < (*firstCharacter)->get_mover().x + 80)
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



// creates new objects 


void Breakthrough::createObject(int x, int y, string object_to_create)
{
    // int random = rand() % 3;
    // if (random == 0)
    // {
    //     Unit pigeon = {{7, 88, 155, 103}, {x, y, 50, 50}};
    //     pigeons.push_back(pigeon);
    // }
    // else if (random == 1)
    // {
    //     Unit butterfly = {{256, 24, 174, 134}, {x, y, 50, 50}};
    //     butterflies.push_back(butterfly);
    // }
    // else 
    // {
    //     Unit bee = {{63, 619, 151, 166}, {x, y, 50, 50}};
    //     bees.push_back(bee);
    // }

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
    std::cout << "length: " << bullets_list.size() << "\n";
    std::cout << ptr << "\n";
    std::cout << "Mouse clicked at: " << x << " -- " << y << std::endl;
}

Breakthrough::~Breakthrough()
{
    for (Unit* unit : characters_list) {
        delete unit;
        unit = nullptr;
    }
}
