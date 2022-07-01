#include "game.h"
#include "const.h"

Game::Game() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		WINDOW_TITLE)
{
	window.setVerticalSyncEnabled(true);
	for (size_t i = 0; i < 20; i++) {
		Bombas* bomba = new Bombas();
		bombas.push_back(bomba);
	}
}

void Game::play() {
	while (window.isOpen()) {
		
		check_events();
		check_colisions();
		update();
		draw();
	}
}

void Game::check_events() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();
		// proverka na gameover
		if (lefttank.getPosition() == Position(99999999, 999999999) || righttank.getPosition() == Position(99999999, 999999999))
		{
			game_state = GAME_OVER;
		}
		// proverka na play
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) {
				game_state = PLAY;
			}
		}
		//klavisha ne nazata
		if (event.type == sf::Event::KeyReleased)
		{
			//pravy tank
			if (event.key.code == sf::Keyboard::Down) {
				righttank.setMoveDown(false);
			}
			if (event.key.code == sf::Keyboard::Left) {
				righttank.setMoveLeft(false);
			}
			if (event.key.code == sf::Keyboard::Right) {
				righttank.setMoveRight(false);
			}
			if (event.key.code == sf::Keyboard::Up) {
				righttank.setMoveUp(false);
			}
			//levy tank
			if (event.key.code == sf::Keyboard::S) {
				lefttank.setMoveDown(false);
			}
			if (event.key.code == sf::Keyboard::A) {
				lefttank.setMoveLeft(false);
			}
			if (event.key.code == sf::Keyboard::D) {
				lefttank.setMoveRight(false);
			}
			if (event.key.code == sf::Keyboard::W) {
				lefttank.setMoveUp(false);
			}
		}
		//klavisha nazata
		if (event.type == sf::Event::KeyPressed) {
			//pravy tank
			//puli dla pravogo tanka
			if (game_state == PLAY && event.key.code == sf::Keyboard::Space) {
				sf::Time now = clock.getElapsedTime();
				if (now.asMilliseconds() > fire_delay) {
					clock.restart();
					RightBullet* new_rghtbull = new RightBullet(
						righttank.getPosition().x + righttank.getHitBox().width/2,
						righttank.getPosition().y + righttank.getHitBox().height / 2
					);
					new_rghtbull->setMove(true);
					rghtbull.push_back(new_rghtbull);
					
				}
			}
			//
			if (event.key.code == sf::Keyboard::Left) {
					righttank.setMoveLeft(true);
			}
			if (event.key.code == sf::Keyboard::Right) {
					righttank.setMoveRight(true);
			}
			if (event.key.code == sf::Keyboard::Up) {
					righttank.setMoveUp(true);
			}
			if (event.key.code == sf::Keyboard::Down) {
				righttank.setMoveDown(true);
			}
			//levy tank
			//puli dla levogo tank
			if (game_state == PLAY && event.key.code == sf::Keyboard::X) {
			sf::Time now = clock.getElapsedTime();
			if (now.asMilliseconds() > fire_delay) {
				clock.restart();
				LeftBullet* new_lftbull = new LeftBullet(
					lefttank.getPosition().x + lefttank.getHitBox().width / 2,
					lefttank.getPosition().y + lefttank.getHitBox().height / 2
				);
				new_lftbull->setMove(true);
				lftbull.push_back(new_lftbull);

			}
		}
			//
			if (event.key.code == sf::Keyboard::A)
			{
				lefttank.setMoveLeft(true);
			}
			if (event.key.code == sf::Keyboard::D)
			{
				lefttank.setMoveRight(true);
			}
			if (event.key.code == sf::Keyboard::W)
			{
				lefttank.setMoveUp(true);
			}
			if (event.key.code == sf::Keyboard::S)
			{
				lefttank.setMoveDown(true);
			}
		}
	}
}

void Game::check_colisions() {
	//pravy tank stalkivaetsa s labirintom
	while ((righttank.getHitBox().intersects(l1.getHitBox())|| righttank.getHitBox().intersects(l2.getHitBox()) ||
		righttank.getHitBox().intersects(l3.getHitBox()) || righttank.getHitBox().intersects(l4.getHitBox()))
		&& righttank.getMoveRight()) {
		righttank.setMoveRight(false);
		righttank.move(-5,0);
	}
	while ((righttank.getHitBox().intersects(l1.getHitBox()) || righttank.getHitBox().intersects(l2.getHitBox()) ||
		righttank.getHitBox().intersects(l3.getHitBox()) || righttank.getHitBox().intersects(l4.getHitBox()))
		&& righttank.getMoveLeft()) {
		righttank.setMoveLeft(false);
		righttank.move(5, 0);
	}
	while ((righttank.getHitBox().intersects(l1.getHitBox()) || righttank.getHitBox().intersects(l2.getHitBox()) ||
		righttank.getHitBox().intersects(l3.getHitBox()) || righttank.getHitBox().intersects(l4.getHitBox()))
		&& righttank.getMoveUp()) {
		righttank.setMoveUp(false);
		righttank.move(0,5);
	}
	while ((righttank.getHitBox().intersects(l1.getHitBox()) || righttank.getHitBox().intersects(l2.getHitBox()) ||
		righttank.getHitBox().intersects(l3.getHitBox()) || righttank.getHitBox().intersects(l4.getHitBox()))
		&& righttank.getMoveDown()) {
		righttank.setMoveDown(false);
		righttank.move(0, -5);
	}
	//levy tank stalkivaetsa s labirintom
	while ((lefttank.getHitBox().intersects(l1.getHitBox()) || lefttank.getHitBox().intersects(l2.getHitBox()) ||
		lefttank.getHitBox().intersects(l3.getHitBox()) || lefttank.getHitBox().intersects(l4.getHitBox()))
		&& lefttank.getMoveRight()) {
		lefttank.setMoveRight(false);
		lefttank.move(-5, 0);
	}
	while ((lefttank.getHitBox().intersects(l1.getHitBox()) || lefttank.getHitBox().intersects(l2.getHitBox()) ||
		lefttank.getHitBox().intersects(l3.getHitBox()) ||lefttank.getHitBox().intersects(l4.getHitBox()))
		&& lefttank.getMoveLeft()) {
		lefttank.setMoveLeft(false);
		lefttank.move(5, 0);
	}
	while ((lefttank.getHitBox().intersects(l1.getHitBox()) || lefttank.getHitBox().intersects(l2.getHitBox()) ||
		lefttank.getHitBox().intersects(l3.getHitBox()) || lefttank.getHitBox().intersects(l4.getHitBox()))
		&& lefttank.getMoveUp()) {
		lefttank.setMoveUp(false);
		lefttank.move(0, 5);
	}
	while ((lefttank.getHitBox().intersects(l1.getHitBox()) || lefttank.getHitBox().intersects(l2.getHitBox()) ||
		lefttank.getHitBox().intersects(l3.getHitBox()) || lefttank.getHitBox().intersects(l4.getHitBox()))
		&& lefttank.getMoveDown()) {
		lefttank.setMoveDown(false);
		lefttank.move(0, -5);
	}
	//pravy tank stolknylsa s bombami
	for (auto iter = bombas.begin(); iter != bombas.end(); iter++) 
	{
		if (righttank.getHitBox().intersects((*iter)->getHitBox())) {
			(*iter)->spawn();
			righttank.hide();
		}
	}
	//levy tank stolknylsa s bombami
	for (auto iter = bombas.begin(); iter != bombas.end(); iter++)

	{
		if (lefttank.getHitBox().intersects((*iter)->getHitBox())) {
			(*iter)->spawn();
			lefttank.hide();
		}
	}
	//levaya pula stolknulas s pravym tankom
	for (auto iter = lftbull.begin(); iter != lftbull.end(); iter++)
	{
		if (righttank.getHitBox().intersects((*iter)->getHitBox())) {
			righttank.hide();
		}
	}
	//pravaya pula stolknulas s levym tankom
	for (auto iter = rghtbull.begin(); iter != rghtbull.end(); iter++)
	{
		if (lefttank.getHitBox().intersects((*iter)->getHitBox())) {
			lefttank.hide();
		}
	}
	//pra
}

void Game::update() {
	
	switch (game_state) {
	case INTRO:
		music.setMusic();
		music.play();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			game_state = PLAY;
		}
		break;
	case PLAY:
		
		righttank.update();
		lefttank.update();
		//pravaya pula stolknylas s levym tankom
		for (auto iter = rghtbull.begin(); iter != rghtbull.end(); iter++) {
			(*iter)->update();
			if ((*iter)->getHitBox().intersects(lefttank.getHitBox())) {
				(*iter)->setDel(true);
			}
		}
		rghtbull.remove_if([](RightBullet* bull) {return bull->getDel(); });
		//pravaya pula stolknylas s pripatstviyami
		for (auto iter = rghtbull.begin(); iter != rghtbull.end(); iter++) {
			(*iter)->update();
			if ((*iter)->getHitBox().intersects(l1.getHitBox())) {
				(*iter)->setDel(true);
			}
		}

		//
		for (auto iter = rghtbull.begin(); iter != rghtbull.end(); iter++) {
			(*iter)->update();
			if ((*iter)->getHitBox().intersects(l2.getHitBox())) {
				(*iter)->setDel(true);
			}
		}

		//
		for (auto iter = rghtbull.begin(); iter != rghtbull.end(); iter++) {
			(*iter)->update();
			if ((*iter)->getHitBox().intersects(l3.getHitBox())) {
				(*iter)->setDel(true);
			}
		}

		//
		for (auto iter = rghtbull.begin(); iter != rghtbull.end(); iter++) {
			(*iter)->update();
			if ((*iter)->getHitBox().intersects(l4.getHitBox())) {
				(*iter)->setDel(true);
			}
		}
		rghtbull.remove_if([](RightBullet* bull) {return bull->getDel(); });
		//
		//
		//levaya pula stolknylas s pravym tankom
		for (auto iter = lftbull.begin(); iter != lftbull.end(); iter++) {
			(*iter)->update();
			if ((*iter)->getHitBox().intersects(righttank.getHitBox())) {
				(*iter)->setDel(true);
			}
		}
		lftbull.remove_if([](LeftBullet* bull) {return bull->getDel(); });
		//levaya pula stolknylas s pripatstvyami
		for (auto iter = lftbull.begin(); iter != lftbull.end(); iter++) {
			(*iter)->update();
			if ((*iter)->getHitBox().intersects(l1.getHitBox())) {
				(*iter)->setDel(true);
			}
		}
		//
		for (auto iter = lftbull.begin(); iter != lftbull.end(); iter++) {
			(*iter)->update();
			if ((*iter)->getHitBox().intersects(l2.getHitBox())) {
				(*iter)->setDel(true);
			}
		}
		//
		for (auto iter = lftbull.begin(); iter != lftbull.end(); iter++) {
			(*iter)->update();
			if ((*iter)->getHitBox().intersects(l3.getHitBox())) {
				(*iter)->setDel(true);
			}
		}
		//
		for (auto iter = lftbull.begin(); iter != lftbull.end(); iter++) {
			(*iter)->update();
			if ((*iter)->getHitBox().intersects(l4.getHitBox())) {
				(*iter)->setDel(true);
			}
		}
		lftbull.remove_if([](LeftBullet* bull) {return bull->getDel(); });
		break;
	case GAME_OVER:
		break;
	}
}

void Game::draw() {
	switch (game_state) {
	case INTRO:
		window.clear(sf::Color::Black);
		intro.draw(window);
		window.display();
		break;
	case PLAY:
		window.clear(sf::Color::Black);
		righttank.draw(window);
		lefttank.draw(window);
		for (size_t i = 0; i < 20; i++) {
			bombas[i]->draw(window);
		}
		for (auto iter = rghtbull.begin(); iter != rghtbull.end(); iter++) {
			(*iter)->draw(window);
		}
		for (auto iter = lftbull.begin(); iter != lftbull.end(); iter++) {
			(*iter)->draw(window);
		}
		l1.draw(window);
		l2.draw(window);
		l3.draw(window);
		l4.draw(window);
		window.display();
		break;
	case GAME_OVER:
		window.clear(sf::Color::Black);
		gameover.draw(window);
		if (lefttank.getPosition() == Position(99999999, 999999999)) {
			text.update("Right Tank Win!!!");
			window.draw(text.getText());
		}
		if (righttank.getPosition() == Position(99999999, 999999999)) {
			text.update("Left Tank Win!!!");
			window.draw(text.getText());
		}
		window.display();
		break;
	}
}