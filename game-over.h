#pragma once
#include "SFML/Graphics.hpp"

class GameOver {
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	GameOver() {
		texture.loadFromFile("gameover.png");
		sprite.setTexture(texture);
	}
	sf::Sprite getSprite() { return sprite; }
	void draw(sf::RenderWindow& window) { window.draw(sprite); };
};