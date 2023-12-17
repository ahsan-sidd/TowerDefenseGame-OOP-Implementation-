#include "game.hpp"

int main(int argc, char *argv[]){
    srand(time(NULL));

    while (true) {
        Game game;

        if (!game.init()) {
            printf("Failed to initialize!\n");
            return 0;
        }

        // game.endGameWin();
        if (game.StartScreen() == false) {
            game.close();
            return 0;
        }

        if (game.characterSelect() == false) {
            game.close();
            return 0;
        }

        if (game.run() == false) {
            game.close();
            return 0;
        }

        game.close();
    }

    //Game doesnt restart right now

    return 0;
}