#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "right-tank.h"
#include "left-tank.h"
#include "bomba.h"
#include "right-bullet.h"
#include "lab1.h"
#include "lab2.h"
#include "lab3.h"
#include "lab4.h"
#include "left-bullet.h"
#include "game-over.h"
#include "intro.h"
#include "text.h"
#include "music.h"


class Game {
public:
	enum GameState { INTRO, PLAY, GAME_OVER };
	Game();
	void play();
private:
	sf::Vector2f Position(int x, int y) { return sf::Vector2f(x, y); }
	sf::RenderWindow window;
	GameState game_state = INTRO;
	RightTank righttank;
	LeftTank lefttank;
	std::vector<Bombas*> bombas;
	std::list<RightBullet*> rghtbull;
	std::list<LeftBullet*> lftbull;
	Labyrinth1 l1;
	Labyrinth2 l2;
	Labyrinth3 l3;
	Labyrinth4 l4;
	GameOver gameover;
	Intro intro;
	Text text;
	Music music;
	sf::Clock clock;
	size_t fire_delay = 200;
	void check_events();
	void update();
	void draw();
	void check_colisions();

	//sf::RenderWindow getWindow() { return window; }
};