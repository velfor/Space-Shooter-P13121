#include "const.h"
#include "meteor.h"

std::string Meteor::meteor_file_names[] =
{ "meteorBrown_big1.png", "meteorBrown_big2.png",
"meteorBrown_big3.png", "meteorBrown_big4.png",
"meteorBrown_med1.png", "meteorBrown_med3.png",
"meteorBrown_small1.png", "meteorBrown_small2.png",
"meteorBrown_tiny1.png", "meteorBrown_tiny2.png" };

Meteor::Meteor() {
	size_t type = rand() % 10;
	texture.loadFromFile(IMAGES_FOLDER + 
		Meteor::meteor_file_names[type]);
	sprite.setTexture(texture);
	float x = rand() % (static_cast<size_t>(WINDOW_WIDTH) - 
		getWidth());
	float y = rand()%(static_cast<size_t>(WINDOW_HEIGHT / 2))- 
		WINDOW_HEIGHT / 2;
	sprite.setPosition(x, y);
	speedx = rand() % 5 - 2;//getRandom(-1,1)
	speedy = rand() % 8 + 3;//getRandom(3,11)
}
void Meteor::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
void Meteor::update() {
	sprite.move(speedx, speedy);
	if (sprite.getPosition().x < 0.f-getWidth() ||
		sprite.getPosition().x > WINDOW_WIDTH ||
		sprite.getPosition().y > WINDOW_HEIGHT
		)
	{
		float startx = rand() % (static_cast<size_t>(WINDOW_WIDTH) - getWidth() + 1);
		float starty = rand() % (static_cast<size_t>(WINDOW_HEIGHT) + 1) - WINDOW_HEIGHT;
		sprite.setPosition(startx, starty);
		speedx = rand() % 5 - 2;
		speedy = rand() % 8 + 3;
	}
}
size_t Meteor::getWidth() { return sprite.getLocalBounds().width; }
size_t Meteor::getHeight() { return sprite.getLocalBounds().height; }
sf::FloatRect Meteor::getHitBox() { return sprite.getGlobalBounds(); }