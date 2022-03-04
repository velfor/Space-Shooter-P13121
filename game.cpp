#include "game.h"
#include "settings.h"
#include <iostream>

Game::Game():
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
		WINDOW_TITLE, 
		sf::Style::Titlebar | sf::Style::Close),
	player_hp("res/kenvector_future.ttf", 24, 550, 10, sf::Color::Yellow),
	game_over_screen(IMAGES_FOLDER + GAME_OVER_FILE_NAME, 1.351f, 2.135f)
{
	window.setVerticalSyncEnabled(true);
	for (size_t i = 0; i < METEORS_QTY; i++) {
		Meteor* meteor = new Meteor();
		meteors.push_back(meteor);
	}

}
void Game::play() {
	while (window.isOpen()) {
		check_events();
		update();
		check_collisions();
		draw();
	}
}
void Game::check_events() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();
		else
			if (event.type == sf::Event::KeyPressed)
				if (game_state == PLAY && event.key.code == sf::Keyboard::Space)
				{
					Laser* new_laser = new Laser(
						player.getPosition().x + player.getHitBox().width / 2,
						player.getPosition().y + player.getHitBox().height / 2
					);
					lasers.push_back(new_laser);
				}
	}
}
void Game::update(){
	switch (game_state) {
	case INTRO:
		break;
	case PLAY:
		player.update();
		for (size_t i = 0; i < METEORS_QTY; i++) {
			meteors[i]->update();
		}
		for (auto iter = lasers.begin(); iter != lasers.end(); iter++) {
			(*iter)->update();
		}
		lasers.remove_if([](Laser* laser) {return laser->getPosition().y < -50; });
		player_hp.update(std::to_string(player.getHp()));
		if (player.getHp() <= 0) game_state = GAME_OVER;
		break;
	case GAME_OVER:
		break;
	}
}
	
void Game::draw() {
	window.clear(sf::Color::Black);

	switch (game_state) {
	case INTRO:
		break;
	case PLAY:
		player.draw(window);
		for (size_t i = 0; i < METEORS_QTY; i++) {
			meteors[i]->draw(window);
		}
		for (auto iter = lasers.begin(); iter != lasers.end(); iter++) {
			(*iter)->draw(window);
		}
		window.draw(player_hp.getText());
		break;
	case GAME_OVER:
		window.draw(game_over_screen.getSprite());
		break;
	}
	
	window.display();
}
void Game::check_collisions() {
	//метеор попал в корабль
	for (auto iter = meteors.begin(); iter != meteors.end(); iter++) {
		if (player.getHitBox().intersects((*iter)->getHitBox())) {
			(*iter)->spawn();
			player.decreaseHp(static_cast<size_t>(
				(*iter)->getHitBox().width/3));
		}
	}
}
