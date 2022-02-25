#pragma once
#include "SFML/Graphics.hpp"

class Player {
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Player();
	void update();
	void draw(sf::RenderWindow& window);
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
};