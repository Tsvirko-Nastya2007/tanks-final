#pragma once
#include "SFML/Graphics.hpp"

class Text
{
private:
	sf::Font font;
	sf::Text text;
public:
	Text()
	{
		font.loadFromFile("FONT.TTF");
		text.setFont(font);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(60);
		text.setPosition(500, 450);
	}
	sf::Text getText() { return text; }
	void update(std::string str) { text.setString(str); }
};