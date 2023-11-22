#include<SDL.h>
#include "game.hpp"


void Attacking3(SDL_Renderer* gRnderer, SDL_Texture* assets);
void Walking(SDL_Renderer* gRnderer, SDL_Texture* assets);
void createNinja(int x, int y);
void Attack(SDL_Renderer* gRnderer, SDL_Texture* assets);
void Jump(SDL_Renderer* gRnderer, SDL_Texture* assets);
void moveRight(SDL_Renderer* gRnderer, SDL_Texture* assets);
void moveLeft(SDL_Renderer* gRnderer, SDL_Texture* assets);
void dropDown(SDL_Renderer* gRnderer, SDL_Texture* assets);

void WalkingFighter(SDL_Renderer* gRenderer, SDL_Texture* assets);
void createFighter(int x, int y);
void FighterAttacking2(SDL_Renderer* gRenderer, SDL_Texture* assets);

enum CharacterState{
	WALKING,
	ATTACKING,
    STRONG,
    DEAD
};

enum CharacterType{
    Shinobi,
    Fighter,
    Samurai
};

struct Unit{
SDL_Rect srcRect, moverRect;
float yVelocity;
float xVelocity;
CharacterState cState;
};

class Sprite{
    protected:
        int health;
        int movementSpeed;
        int damage;

        SDL_Texture* spriteTexture;
        // SDL_Rect spriteRect;
        Unit Char;
        Game game1;

    public:
        Sprite(SDL_Renderer* renderer, const std::string& imgPath, int initialHealth, int Speed, int dmg);

        virtual ~Sprite();

        int getHealth() const;

        void takeDamage(int d);

        virtual void move() = 0; //implement movement in child classes

        void render(SDL_Renderer* renderer);

};

class CharacterSprite :public Sprite{

    CharacterType c_Type;

    public:

    CharacterSprite(SDL_Renderer* renderer, const std::string& imagePath, int initialHealth, int speed, int dmg, CharacterType x);

    void move() override{};

};
