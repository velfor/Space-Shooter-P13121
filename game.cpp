﻿#include "game.h"
#include "settings.h"
#include <iostream>

Game::Game():
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
		WINDOW_TITLE, 
		sf::Style::Titlebar | sf::Style::Close),
	player_hp("res/kenvector_future.ttf", 24, 550, 5, sf::Color::Yellow),
	score_text("res/kenvector_future.ttf", 24, 10, 5, sf::Color::Yellow),
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
					sf::Time now = clock.getElapsedTime();
					if (now.asMilliseconds() > fire_delay) {
						clock.restart();
						Laser* new_laser = new Laser(
							player.getPosition().x + player.getHitBox().width / 2,
							player.getPosition().y + player.getHitBox().height / 2
						);
						lasers.push_back(new_laser);
					}
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
		score_text.update("Score: " + std::to_string(score));
		if (player.getHp() <= 0) game_state = GAME_OVER;
		for (auto iter = bonuses.begin(); iter != bonuses.end(); iter++) {
			(*iter)->update();
		}
		for (auto iter = explosions.begin(); iter != explosions.end(); iter++) {
			(*iter)->update();
		}
		break;
	case GAME_OVER:
		break;
	}
}
	
void Game::draw() {
	window.clear(sf::Color::Black);
	sf::RectangleShape r1(sf::Vector2f(WINDOW_WIDTH, 40));
	r1.setFillColor(sf::Color::Blue);
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
		window.draw(r1);
		window.draw(player_hp.getText());
		window.draw(score_text.getText());
		for (auto iter = bonuses.begin(); iter != bonuses.end(); iter++) {
			(*iter)->draw(window);
		}
		for (auto iter = explosions.begin(); iter != explosions.end(); iter++) {
			(*iter)->draw(window);
		}
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
	//пули попали в метеоры
	for (auto it_l = lasers.begin(); it_l != lasers.end(); it_l++) {
		for (auto it_m = meteors.begin(); it_m != meteors.end(); it_m++) {
			if ((*it_l)->getHitBox().intersects((*it_m)->getHitBox())){
				score += 50 - static_cast<size_t>((*it_m)->getHitBox().width / 3);
				Explosion* new_exp = new Explosion((*it_m)->getPosition());
				explosions.push_back(new_exp);
				(*it_m)->spawn();
				(*it_l)->setDel(true);
				//с 10% шансом из метеора выпадает бонус
				size_t chance = rand() % 1000;
				if (chance < 100) {
					Bonus* new_bonus = new Bonus((*it_m)->getPosition());
					bonuses.push_back(new_bonus);
				}
			}
		}
	}
	//удаляем помеченные пули
	lasers.remove_if([](Laser* laser) {return laser->getDel(); });
	//удаляем помеченные взрывы
	explosions.remove_if([](Explosion* exp) {return exp->getDel(); });
	//бонус попал в корабль
	for (auto iter = bonuses.begin(); iter != bonuses.end(); iter++) {
		if (player.getHitBox().intersects((*iter)->getHitBox())) {
			(*iter)->setDel(true);
			switch ((*iter)->getType()) {
			case Bonus::BonusType::PILL:
				player.increaseHp(25);
				break;
			}
		}
	}
	//удаляем помеченные бонусы
	bonuses.remove_if([](Bonus* bonus) {return bonus->getDel(); });

}
