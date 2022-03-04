#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include "meteor.h"
#include "laser.h"
#include <vector>
#include <list>
#include "text.h"
#include "splash.h"

class Game {
public:
	enum GameState {INTRO, PLAY, GAME_OVER};
	Game();
	void play();
private:
	sf::RenderWindow window;
	GameState game_state = PLAY;
	Player player;
	std::vector<Meteor*> meteors;
	std::list<Laser*> lasers;
	TextObject player_hp;
	SplashScreen game_over_screen;

	void check_events();
	void update();
	void draw();
	void check_collisions();
};
