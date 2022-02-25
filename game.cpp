#include "game.h"
#include "settings.h"

Game::Game():
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
		WINDOW_TITLE, 
		sf::Style::Titlebar | sf::Style::Close)
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
	player.update();
	for (size_t i = 0; i < METEORS_QTY; i++) {
		meteors[i]->update();
	}
	for (auto iter = lasers.begin(); iter != lasers.end(); iter++) {
		(*iter)->update();
	}
	for (auto iter = lasers.begin(); iter != lasers.end(); iter++) {
		sf::Vector2f pos = (*iter)->getPosition();
		float height = (*iter)->getHitBox().height;
		if (pos.y - height < 0) {

			lasers.erase(iter);
		}
	}
}
void Game::draw() {
	window.clear(sf::Color::Black);
	player.draw(window);
	for (size_t i = 0; i < METEORS_QTY; i++) {
		meteors[i]->draw(window);
	}
	for (auto iter = lasers.begin(); iter != lasers.end(); iter++) {
		(*iter)->draw(window);
	}
	window.display();
}
