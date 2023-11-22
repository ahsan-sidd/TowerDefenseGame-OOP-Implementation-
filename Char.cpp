#include<iostream>
#include "Char.hpp"
#include <vector>
#include <random>
#include "HealthBar.hpp"
// # include <gif-lib.h>
using namespace std;

Unit Walk = {{22,53,79,75},{0,734,99,94}, 0, 0};
//1.25 multiplication of the width and height from the srcRect to make the characters look more appealing.

vector<Unit> Ninjas;
vector<Unit> Fighters;

// Initialize counters for animation frames (Used to control the animation status automatically for each object)

int aNum = 0;
int walkNum = 0;

int fWalk = 0;
int FaNum = 0;

void Attacking3(SDL_Renderer* gRenderer, SDL_Texture* assets){
    for (Unit& Ninja : Ninjas) {
        // Update the x-coordinate of the moverRect
        // if (Ninja.moverRect.x > 1000) {
        //     Ninja.moverRect.x = 0;
        // } else {
        //     Ninja.moverRect.x += 1;
        //     SDL_Delay(1000);
        // }
        if (aNum == 0){
            Ninja.srcRect = {22,53,79,75};
            Ninja.moverRect.w = 99;
            aNum += 1;
        }
        else if (aNum == 1){
            Ninja.srcRect = {151, 53, 100, 75};
            Ninja.moverRect.w = 125;
            Ninja.moverRect.h = 94;
            aNum += 1;
        }
        else if (aNum == 2){
            Ninja.srcRect = {280, 53, 101, 75};
            Ninja.moverRect.w = 125;
            Ninja.moverRect.h = 94;
            aNum = 0;
        }

        // assets = game.loadTexture("Assets/Walk.png");

        SDL_RenderCopy(gRenderer, assets, &Ninja.srcRect, &Ninja.moverRect);
    }
}

void FighterAttacking2(SDL_Renderer* gRenderer, SDL_Texture* assets){
    for (Unit& Ninja : Fighters) {
        // Update the x-coordinate of the moverRect
        // if (Ninja.moverRect.x > 1000) {
        //     Ninja.moverRect.x = 0;
        // } else {
        //     Ninja.moverRect.x += 1;
        //     SDL_Delay(1000);
        // }
        if (FaNum == 0){
            Ninja.srcRect = {22,53,79,75};
            Ninja.moverRect.w = 99;
            FaNum += 1;
        }
        else if (FaNum == 1){
            Ninja.srcRect = {151, 53, 100, 75};
            Ninja.moverRect.w = 125;
            Ninja.moverRect.h = 94;
            FaNum += 1;
        }
        else if (FaNum == 2){
            Ninja.srcRect = {280, 53, 101, 75};
            Ninja.moverRect.w = 125;
            Ninja.moverRect.h = 94;
            FaNum = 0;
        }

        // assets = game.loadTexture("Assets/Walk.png");

        SDL_RenderCopy(gRenderer, assets, &Ninja.srcRect, &Ninja.moverRect);
    }
}

void Walking(SDL_Renderer* gRenderer, SDL_Texture* assets){
    for (Unit& Ninja : Ninjas) {
        // Update the x-coordinate of the moverRect
        // if (Ninja.moverRect.x > 1000) {
        //     Ninja.moverRect.x = 0;
        // } else {
        //     Ninja.moverRect.x += 1;
        //     SDL_Delay(1000);
        // }
        if (walkNum == 0){
            Ninja.srcRect = {26, 45, 48, 83};
            Ninja.moverRect.w = 60;
            Ninja.moverRect.h = 104;
            walkNum += 1;
        }
        else if (walkNum == 1){
            Ninja.srcRect = {154, 44, 48, 84};
            Ninja.moverRect.w = 60;
            Ninja.moverRect.h = 104;
            walkNum += 1;
        }
        else if (walkNum == 2){
            Ninja.srcRect = {282, 45, 51, 83};
            Ninja.moverRect.w = 64;
            Ninja.moverRect.h = 104;
            walkNum += 1;
        }
        else if (walkNum == 3){
            Ninja.srcRect = {410, 46, 48, 82};
            Ninja.moverRect.w = 60;
            Ninja.moverRect.h = 104;
            walkNum += 1;
        }
        else if (walkNum == 4){
            Ninja.srcRect = {538, 45, 48, 83};
            Ninja.moverRect.w = 60;
            Ninja.moverRect.h = 104;
            walkNum += 1;
        }
        else if (walkNum == 5){
            Ninja.srcRect = {666, 44, 48, 84};
            Ninja.moverRect.w = 60;
            Ninja.moverRect.h = 104;
            walkNum += 1;
        }
        else if (walkNum == 6){
            Ninja.srcRect = {794, 45, 52, 83};
            Ninja.moverRect.w = 64;
            Ninja.moverRect.h = 104;
            walkNum += 1;
        }
        else if (walkNum == 7){
            Ninja.srcRect = {922, 46, 48, 82};
            Ninja.moverRect.w = 60;
            Ninja.moverRect.h = 104;
            walkNum = 0;
        }

        if (Ninja.moverRect.x < (800)){
        Ninja.moverRect.x += 7;
        }

        // assets = game.loadTexture("Assets/Walk.png");

        SDL_RenderCopy(gRenderer, assets, &Ninja.srcRect, &Ninja.moverRect);
    }

    
}

void WalkingFighter(SDL_Renderer* gRenderer, SDL_Texture* assets){
        for (Unit& Ninja : Fighters) {
        // Update the x-coordinate of the moverRect
        // if (Ninja.moverRect.x > 1000) {
        //     Ninja.moverRect.x = 0;
        // } else {
        //     Ninja.moverRect.x += 1;
        //     SDL_Delay(1000);
        // }
        if (fWalk == 0){
            Ninja.srcRect = {26, 45, 48, 83};
            Ninja.moverRect.w = 60;
            Ninja.moverRect.h = 104;
            fWalk += 1;
        }
        else if (fWalk == 1){
            Ninja.srcRect = {154, 44, 48, 84};
            Ninja.moverRect.w = 60;
            Ninja.moverRect.h = 104;
            fWalk += 1;
        }
        else if (fWalk == 2){
            Ninja.srcRect = {282, 45, 51, 83};
            Ninja.moverRect.w = 64;
            Ninja.moverRect.h = 104;
            fWalk += 1;
        }
        else if (fWalk == 3){
            Ninja.srcRect = {410, 46, 48, 82};
            Ninja.moverRect.w = 60;
            Ninja.moverRect.h = 104;
            fWalk += 1;
        }
        else if (fWalk == 4){
            Ninja.srcRect = {538, 45, 48, 83};
            Ninja.moverRect.w = 60;
            Ninja.moverRect.h = 104;
            fWalk += 1;
        }
        else if (fWalk == 5){
            Ninja.srcRect = {666, 44, 48, 84};
            Ninja.moverRect.w = 60;
            Ninja.moverRect.h = 104;
            fWalk += 1;
        }
        else if (fWalk == 6){
            Ninja.srcRect = {794, 45, 52, 83};
            Ninja.moverRect.w = 64;
            Ninja.moverRect.h = 104;
            fWalk += 1;
        }
        else if (fWalk == 7){
            Ninja.srcRect = {922, 46, 48, 82};
            Ninja.moverRect.w = 60;
            Ninja.moverRect.h = 104;
            fWalk = 0;
        }

        if (Ninja.moverRect.x < (800)){
        Ninja.moverRect.x += 7;
        }

        // assets = game.loadTexture("Assets/Walk.png");

        SDL_RenderCopy(gRenderer, assets, &Ninja.srcRect, &Ninja.moverRect);
    }

    
}

void createNinja(int x, int y){
        if (Ninjas.size() == 2){
            return;
        }
        Unit Shinobi = Walk;
        Shinobi.moverRect.x = 0;
        Shinobi.moverRect.y = 734-94;
        Ninjas.push_back(Shinobi);
}

void createFighter(int x, int y){
    if (Fighters.size() == 2){
        return;
    }
    Unit Fighter = Walk;
    Fighter.moverRect.x = 0;
    Fighter.moverRect.y = 734-94;
    Fighters.push_back(Fighter);

}

void Attack(SDL_Renderer* gRenderer, SDL_Texture* assets){
    for (Unit& Ninja : Ninjas){
        Ninja.srcRect = {151, 53, 100, 75};
        SDL_RenderCopy(gRenderer, assets, &Ninja.srcRect, &Ninja.moverRect);
        SDL_Delay(500);
        Ninja.srcRect = {280, 53, 101, 75};
        SDL_RenderCopy(gRenderer, assets, &Ninja.srcRect, &Ninja.moverRect);
        // SDL_Delay(500);
        Ninja.srcRect = {22,53,79,75};
    }
}

void Jump(SDL_Renderer* gRenderer, SDL_Texture* assets){
        Ninjas[0].yVelocity = 10;
        Ninjas[0].moverRect.y -= Ninjas[0].yVelocity;
    // if (Ninjas[0].moverRect.y = (566-150)){
    //     while(Ninjas[0].moverRect.y <= (566-150)){
    //         Ninjas[0].moverRect.y -= Ninjas[0].yVelocity;
    //         Ninjas[0].yVelocity += 3;
    //     }
    //     Ninjas[0].yVelocity = 0;

    // }
    return;
}

void moveRight(SDL_Renderer* gRenderer, SDL_Texture* assets){
        Ninjas[0].xVelocity = 10;
        Ninjas[0].moverRect.x += Ninjas[0].xVelocity;
    return;
}

void moveLeft(SDL_Renderer* gRenderer, SDL_Texture* assets){
        Ninjas[0].xVelocity = 10;
        Ninjas[0].moverRect.x -= Ninjas[0].xVelocity;
    return;
}

void dropDown(SDL_Renderer* gRenderer, SDL_Texture* assets){
        Ninjas[0].yVelocity = 10;
        Ninjas[0].moverRect.y += Ninjas[0].yVelocity;
    return;
}

    CharacterSprite::CharacterSprite(SDL_Renderer* renderer, const std::string& imagePath, int initialHealth, int speed, int dmg, CharacterType x)
        : Sprite(renderer, imagePath, initialHealth, speed, dmg), c_Type(x) {}

    void Sprite::render(SDL_Renderer* renderer){
            SDL_RenderCopy(renderer, spriteTexture, &Char.srcRect, &Char.moverRect);
        }

    void Sprite::takeDamage(int d){
            health -= d;
            if (health <= 0){
                    //Need to figure out destruction/removal logic
            }
        }

    int Sprite::getHealth() const {return health;}

    Sprite::~Sprite(){
        SDL_DestroyTexture(spriteTexture);
        spriteTexture = nullptr;
    }

    Sprite::Sprite(SDL_Renderer* renderer, const std::string& imgPath, int initialHealth, int Speed, int dmg)
        : health(initialHealth), movementSpeed(Speed), damage(dmg){
            
        spriteTexture = game1.loadTexture(imgPath);

        Char.srcRect = {0,0,0,0};
        Char.moverRect = {0,0,0,0};
    }