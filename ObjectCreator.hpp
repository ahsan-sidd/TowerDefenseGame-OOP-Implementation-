#include <SDL.h>
#include "Unit.hpp"
// #include <vector>

class ObjectCreator
{
private:
    int x;
    int y;
    // std::vector<Unit*> object_list;
public:
    Unit* getObject(int new_x, int new_y);
};