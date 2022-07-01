#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Music {
private:
	sf::Music music;
public:
	Music()
	{
		music.openFromFile("tanks.wav");
		music.setVolume(100);
	}
	int setMusic() { 
		if (!music.openFromFile("tanks.wav"))
		{
			return -1;
		}}
	void play() { return music.play(); }
};