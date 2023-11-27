#include <SDL.h>
#include "ObjectCreator.hpp"
#include "Ninja.hpp"
#include <iostream>

Unit* ObjectCreator::getObject(int new_x, int new_y)
{
    int random = rand() % 3;
    if (random == 0 || random == 1 || random == 2)
    {
        // Unit pigeon = {{7, 88, 155, 103}, {new_x, new_y, 50, 50}};
        // return &pigeon;
        return new Ninja({0, 0, 128, 128}, {new_x, 558, 160, 160});
    }
    // else if (random == 1)
    // {
    //     return new Butterfly({256, 24, 174, 134}, {new_x, new_y, 50, 50});
    // }
    // else 
    // {
    //     return new Bee({409, 650, 171, 147}, {new_x, new_y, 50, 50});
    // }
}