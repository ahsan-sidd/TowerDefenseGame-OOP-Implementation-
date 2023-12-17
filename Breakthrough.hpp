#include<SDL.h>
#include<vector>
#include<list>
#include "Unit.hpp"
#include <string>
using namespace std;

class Breakthrough{
    public:
    list<Unit*> characters_list;
    list<Unit*> bullets_list;
    void drawObjects(); 
    void detect_collision();
    void createObject(int x, int y, string object_to_create);
    ~Breakthrough();
};