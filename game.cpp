#include "game.h"
#include "settings.h"

Game::Game():
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
		WINDOW_TITLE, 
		sf::Style::Titlebar | sf::Style::Close)
{
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(FPS);
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
	}
}
void Game::update(){
	player.update();
}
void Game::draw() {
	window.clear(sf::Color::Black);
	player.draw(window);
	window.display();
}
