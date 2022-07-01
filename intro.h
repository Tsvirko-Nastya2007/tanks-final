#pragma once
#include "SFML/Graphics.hpp"

class Intro {
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Intro() {
		texture.loadFromFile("intro.png");
		sprite.setTexture(texture);
	}
	sf::Sprite getSprite() { return sprite; }
	void draw(sf::RenderWindow& window) { window.draw(sprite); };
};