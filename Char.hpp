#include<SDL.h>


void Attacking3(SDL_Renderer* gRnderer, SDL_Texture* assets);
void Walking(SDL_Renderer* gRnderer, SDL_Texture* assets);
void createObject(int x, int y);
void Attack(SDL_Renderer* gRnderer, SDL_Texture* assets);
void Jump(SDL_Renderer* gRnderer, SDL_Texture* assets);
void moveRight(SDL_Renderer* gRnderer, SDL_Texture* assets);
void moveLeft(SDL_Renderer* gRnderer, SDL_Texture* assets);
void dropDown(SDL_Renderer* gRnderer, SDL_Texture* assets);

struct Unit{
SDL_Rect srcRect, moverRect;
float yVelocity;
float xVelocity;
};