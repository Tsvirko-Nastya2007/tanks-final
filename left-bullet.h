#pragma once
#include "const.h"
#include "SFML/Graphics.hpp"

class LeftBullet {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	bool del = false;
	bool move = false;
public:
	LeftBullet(float x, float y) {
		texture.loadFromFile("bullet.png");
		sprite.setTexture(texture);
		sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y - sprite.getGlobalBounds().height / 2);
	}
	void update() {
		if (move)
		{
			sprite.move(3.f, 0.f);
		}
	};
	void draw(sf::RenderWindow& window) { window.draw(sprite); };
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); };
	sf::Vector2f getPosition() { return sprite.getPosition(); };
	void setDel(bool a) { del = a; };
	bool getDel() { return del; };
	void setMove(bool state) { move = state; }
	bool getMove() { return move; }
};