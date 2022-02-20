#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include "meteor.h"
#include <vector>

class Game {
public:
	enum GameState {INTRO, PLAY, GAME_OVER};
	Game();
	void play();
private:
	sf::RenderWindow window;
	Player player;
	std::vector<Meteor*> meteors;
	void check_events();
	void update();
	void draw();
};
