#pragma once

#include <SFML/Audio.hpp>

#include "Animation.h"
#include "Globals.h"



class Objective
{

private:

	sf::Sprite sprite;
	sf::Texture texture;
	Animation animation;

	bool done = false;

	sf::Sound sound_pick_up;
	sf::SoundBuffer buffer_pick_up;


public:

	Objective();
	~Objective();

	void setPosition(float x, float y);
	void setTexture(sf::Texture& texture, int numberOfFrames);
	void setStatus(bool status);

	sf::Sprite getSprite();
	bool isDone();

	void update(float deltaTime, sf::FloatRect heroBoundingBox);
	void draw(sf::RenderWindow& window);
};
