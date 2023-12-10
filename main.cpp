#include "game.hpp"

int main(int argc, char *argv[]){
    Game game;
    srand(time(NULL));
    if( !game.init() ){
		printf( "Failed to initialize!\n" );
        return 0;
	}
		//Load media
    if( !game.loadMedia() ){
        printf( "Failed to load media!\n" );
        return 0;
    }
    // game.StartScreen();
    if (game.StartScreen() == false){
        game.close();
        return 0;
    }
    if (game.characterSelect() == false){
        game.close();
        return 0;
    }
    // game.characterSelect();
    game.run();
    game.close();

    return 0;
}