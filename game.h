#pragma once
#include "const.h"
#include "SFML/Graphics.hpp"
#include "player.h"
#include "meteor.h"
#include <vector>
#include "splash.h"
#include <list>
#include "laser.h"

class Game {
public:
	enum GameState {INTRO, PLAY, PAUSE, GAME_OVER};
	Game();
	void play();
private:
	void check_events();
	void update();
	void draw();
	void check_collisions();

	sf::RenderWindow window;
	Player player;
	GameState game_state = PLAY;
	Splash game_over;
	std::vector<Meteor*> meteor_sprites;
	std::list<Laser*> laser_sprites;
	
};

