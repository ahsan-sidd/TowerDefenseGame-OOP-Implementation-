#include<iostream>
#include "Char.hpp"
#include <vector>
#include <random>
// # include <gif-lib.h>
using namespace std;


Unit Walk = {{22,53,79,75},{30,40,202,150}, 0, 0};

vector<Unit> Ninjas;

// Initialize counters for animation frames (Used to control the animation status automatically for each object)

int num = 0;

void drawObjects(SDL_Renderer* gRenderer, SDL_Texture* assets){
    for (Unit& Ninja : Ninjas) {
        // Update the x-coordinate of the moverRect
        // if (Ninja.moverRect.x > 1000) {
        //     Ninja.moverRect.x = 0;
        // } else {
        //     Ninja.moverRect.x += 1;
        //     SDL_Delay(1000);
        // }
        if (num == 0){
            Ninja.srcRect = {22,53,79,75};
            num += 1;
        }
        else if (num == 1){
            Ninja.srcRect = {151, 53, 100, 75};
            num += 1;
        }
        else if (num == 2){
        Ninja.srcRect = {280, 53, 101, 75};
        num = 0;
        }
        SDL_RenderCopy(gRenderer, assets, &Ninja.srcRect, &Ninja.moverRect);
    }
}

void createObject(int x, int y){
        if (Ninjas.size() == 1){
            return;
        }
        Unit Shinobi = Walk;
        Shinobi.moverRect.x = x;
        Shinobi.moverRect.y = 566-150;
        Ninjas.push_back(Shinobi);
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
        Ninjas[0].moverRect.x += Ninjas[0].yVelocity;
    return;
}

void moveLeft(SDL_Renderer* gRenderer, SDL_Texture* assets){
        Ninjas[0].xVelocity = 10;
        Ninjas[0].moverRect.x -= Ninjas[0].yVelocity;
    return;
}

void dropDown(SDL_Renderer* gRenderer, SDL_Texture* assets){
        Ninjas[0].yVelocity = 10;
        Ninjas[0].moverRect.y += Ninjas[0].yVelocity;
    return;
}
        // if (bee_num == 0) {
        //     bee.srcRect = {340,160,296,288};
        // }


        // Update the srcRect based on the bee_num
        // if (bee_num == 0) {
        //     bee.srcRect = {540, 370, 193, 115};
        //     bee_num += 1;
        // } else if (bee_num == 1) {
        //     bee.srcRect = {527, 138, 194, 115};
        //     bee_num += 1;
        // } else if (bee_num == 2) {
        //     bee.srcRect = {527, 138, 194, 115};
        //     bee_num = 0;
        // }
        
        // Render the bee on the screen

/*
// Function to draw objects on the screen
void drawObjects(SDL_Renderer* gRenderer, SDL_Texture* assets) {
    // Iterate over the bees vector
    for (Unit& bee : bees) {
        // Update the x-coordinate of the moverRect
        if (bee.moverRect.x > 1000) {
            bee.moverRect.x = 0;
        } else {
            bee.moverRect.x += 1;
        }
        
        // Update the srcRect based on the bee_num
        if (bee_num == 0) {
            bee.srcRect = {540, 370, 193, 115};
            bee_num += 1;
        } else if (bee_num == 1) {
            bee.srcRect = {527, 138, 194, 115};
            bee_num += 1;
        } else if (bee_num == 2) {
            bee.srcRect = {527, 138, 194, 115};
            bee_num = 0;
        }
        
        // Render the bee on the screen
        SDL_RenderCopy(gRenderer, assets, &bee.srcRect, &bee.moverRect);
    }
    
    // Iterate over the butterflies vector
    for (Unit& butterfly : butterflies) {
        // Update the x-coordinate of the moverRect
        if (butterfly.moverRect.x > 1000) {
            butterfly.moverRect.x = 0;
        } else {
            butterfly.moverRect.x += 3;
        }
        
        // Update the srcRect based on the butterfly_num
        if (butterfly_num == 0) {
            butterfly.srcRect = {257, 24, 173, 134};
            butterfly_num += 1;
        } else if (butterfly_num == 1) {
            butterfly.srcRect = {257, 182, 192, 214};
            butterfly_num += 1;
        } else if (butterfly_num == 2) {
            butterfly.srcRect = {248, 432, 248, 179};
            butterfly_num = 0;
        }
        
        // Render the butterfly on the screen
        SDL_RenderCopy(gRenderer, assets, &butterfly.srcRect, &butterfly.moverRect);
    }
    
    // Iterate over the pigeons vector
    for (Unit& pigeon : pigeons) {
        // Update the x-coordinate of the moverRect
        if (pigeon.moverRect.x > 1000) {
            pigeon.moverRect.x = 0;
        } else {
            pigeon.moverRect.x += 5;
        }
        
        // Update the srcRect based on the pigeon_num
        if (pigeon_num == 0) {
            pigeon.srcRect = {7, 88, 155, 103};
            pigeon_num += 1;
        } else if (pigeon_num == 1) {
            pigeon.srcRect = {0, 237, 153, 84};
            pigeon_num += 1;
        } else if (pigeon_num == 2) {
            pigeon.srcRect = {2, 361, 159, 124};
            pigeon_num = 0;
        }
        
        // Render the pigeon on the screen
        SDL_RenderCopy(gRenderer, assets, &pigeon.srcRect, &pigeon.moverRect);
    }
}

// Function to create objects randomly
void createObject(int x, int y) {
    // Generate a random number between 0 and 2
    int num = rand() % 3;
    
    // Create an object based on the random number and push it into the corresponding vector
    if (num == 0) {
        Unit bee = bee_straight;
        bee.moverRect.x = x;
        bee.moverRect.y = y;
        bees.push_back(bee);
    } else if (num == 1) {
        Unit pigeonU = pigeon;
        pigeonU.moverRect.x = x;
        pigeonU.moverRect.y = y;
        pigeons.push_back(pigeonU);
    } else if (num == 2) {
        Unit butterfly = butterfly_straight;
        butterfly.moverRect.x = x;
        butterfly.moverRect.y = y;
        butterflies.push_back(butterfly);
    }
}
*/