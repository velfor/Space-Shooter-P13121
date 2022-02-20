#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"

class Game {
public:
	enum GameState {INTRO, PLAY, GAME_OVER};
	Game();
	void play();
private:
	sf::RenderWindow window;
	Player player;

	void check_events();
	void update();
	void draw();
};
