#pragma once
#include "SFML/Graphics.hpp"

class Laser {
private:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Laser(float, float);
	void draw(sf::RenderWindow& window);
	void update();
	size_t getWidth();
	size_t getHeight();
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
};
