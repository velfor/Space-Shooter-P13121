#pragma once
#include "SFML/Graphics.hpp"

class Laser {
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Laser();
	void update();
	void draw();
};