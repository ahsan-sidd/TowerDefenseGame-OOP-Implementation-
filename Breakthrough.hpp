#include<SDL.h>
#include<vector>
#include<list>
#include "Unit.hpp"
#include <string>
using namespace std;

class Breakthrough{

    //Right now we're creating one pigeon, just for practice. for details follow the guidlines 
    // Pigeon p1;


    //Create your list here
    public:
    list<Unit*> characters_list;
    list<Unit*> bullets_list;
    void drawObjects(); 
    void createObject(int x, int y, string object_to_create);
    ~Breakthrough();
    
    // create destructor which deletes all dynamic objects
};