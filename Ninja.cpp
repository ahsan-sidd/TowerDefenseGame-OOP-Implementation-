#include "Ninja.hpp"
#include <iostream>
#include "game.hpp"
// pigeon implementation will go here.


// in project implementation this draw function should only be in superclass
// void Pigeon::draw(){
//     SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
// }


// fly() is overrided from the superclass
Game game;

void Ninja::move(){
    //
    if (get_mover().x < 850)
    {
        if (movement_frame == 0)
        {
            get_src().x = 26;
            get_src().y = 45;
            get_src().w = 48;
            get_src().h = 83;
        }
        else if (movement_frame == 1)
        {
            get_src().x = 154;
            get_src().y = 44;
            get_src().w = 48;
            get_src().h = 84;
        }
        else if (movement_frame == 2)
        {
            get_src().x = 282;
            get_src().y = 45;
            get_src().w = 51;
            get_src().h = 83;
        }
        else if (movement_frame == 3)
        {
            get_src().x = 410;
            get_src().y = 46;
            get_src().w = 48;
            get_src().h = 82;
        }
        else if (movement_frame == 4)
        {
            get_src().x = 538;
            get_src().y = 45;
            get_src().w = 48;
            get_src().h = 83;
        }
        else if (movement_frame == 5)
        {
            get_src().x = 666;
            get_src().y = 44;
            get_src().w = 48;
            get_src().h = 84;
        }
        else if (movement_frame == 6)
        {
            get_src().x = 794;
            get_src().y = 45;
            get_src().w = 52;
            get_src().h = 83;
        }
        else if (movement_frame == 7)
        {
            get_src().x = 922;
            get_src().y = 46;
            get_src().w = 48;
            get_src().h = 82;
            movement_frame = 0;
        }
        movement_frame++;
        get_mover().x += movement_speed;
    }
    else
    {
        attack();
    }
}

void Ninja::attack()
{
    game.assets = game.loadTexture("Assets/Samurai/Attack_1.png");
    if (attack_frame == 0)
    {
        get_src().x = 23;
        get_src().y = 54;
        get_src().w = 53;
        get_src().h = 74;   
    }
    else if (attack_frame == 1)
    {
        get_src().x = 152;
        get_src().y = 55;
        get_src().w = 52;
        get_src().h = 73;
    }
    else if (attack_frame == 2)
    {
        get_src().x = 280;      
        get_src().y = 55;
        get_src().w = 57;
        get_src().h = 73;
    }
    else if (attack_frame == 3)
    {
        get_src().x = 408;      
        get_src().y = 54;
        get_src().w = 63;
        get_src().h = 74;
    }
    else if (attack_frame == 4)
    {
        get_src().x = 536;      
        get_src().y = 54;
        get_src().w = 101;
        get_src().h = 74;
    }
    else if (attack_frame == 5)
    {
        get_src().x = 664;      
        get_src().y = 54;
        get_src().w = 54;
        get_src().h = 74;
        attack_frame = 0;
        SDL_Delay(300);
    }
    attack_frame++;
    // if (attack_frame == 0)
    // {
    //     get_src().x = 151;      
    //     get_src().y = 53;
    //     get_src().w = 100;
    //     get_src().h = 75;
    // }
    // else if (attack_frame == 1)
    // {
    //     get_src().x = 280;      
    //     get_src().y = 53;
    //     get_src().w = 101;
    //     get_src().h = 75;
    // }
    // else if (attack_frame == 2)
    // {
    //     get_src().x = 23;      
    //     get_src().y = 53;
    //     get_src().w = 79;
    //     get_src().h = 75;
    //     attack_frame = 0;
    // }
    // attack_frame++;
    // SDL_Delay(500);
}

    // src coorinates from assets.png file, they have been found using spritecow.com
Ninja::Ninja(SDL_Rect s, SDL_Rect m) : Unit(s, m){
    // srcRect = s;
    // moverRect = m;
    // srcRect = {7,88,160,103};

    // it will display pigeon on x = 30, y = 40 location, the size of pigeon is 50 width, 60 height
    // moverRect = {30, 40, 50, 50};
}

