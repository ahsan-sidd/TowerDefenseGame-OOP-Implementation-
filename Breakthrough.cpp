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
