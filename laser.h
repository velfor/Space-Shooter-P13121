#pragma once
#include "SFML/Graphics.hpp"

class Laser {
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Laser(float x , float y);
	void update();
	void draw(sf::RenderWindow& );
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
};