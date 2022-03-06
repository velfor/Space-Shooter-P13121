#pragma once
#include "SFML/Graphics.hpp"

class Bonus {
public:
	enum class BonusType {BOLT, PILL, SHIELD, STAR};
	Bonus(sf::Vector2f pos);
	void update();
	void draw(sf::RenderWindow&);
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
	BonusType getType();
	void setDel(bool);
	bool getDel();
private:
	sf::Texture texture;
	sf::Sprite sprite;
	static std::string bonus_file_names[];
	BonusType type;
	bool del = false;

};
