#include "laser.h"
#include "const.h"

Laser::Laser(float x, float y) {
	texture.loadFromFile(IMAGES_FOLDER + LASER_FILE_NAME);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}
void Laser::update() {
	sprite.move(0.f, -LASER_SPEEDY);
}
size_t Laser::getWidth() { return sprite.getLocalBounds().width; }
size_t Laser::getHeight() { return sprite.getLocalBounds().height; }
sf::FloatRect Laser::getHitBox() { return sprite.getGlobalBounds(); }
void Laser::draw(sf::RenderWindow& window) { window.draw(sprite); }