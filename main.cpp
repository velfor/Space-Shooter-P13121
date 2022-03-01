#include "SFML/Graphics.hpp"
#include "game.h"
#include <ctime>
using namespace sf;

int main(){
	srand(time(0));
	rand();
	Game game;
	game.play();
	return 0;
}