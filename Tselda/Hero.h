#pragma once

#include <SFML/Audio.hpp>

#include "Animation.h"
#include "Npc.h"
#include "Enemy.h"
#include "UI.h"



class Hero
{

private:

	// constants
	const static int DOWN = 0;
	const static int UP = 1;
	const static int RIGHT = 2;
	const static int LEFT = 3;

	sf::Sprite heroSprite;
	sf::Texture heroTexture;
	Animation heroAnimation;

	sf::Sprite swordSprite;
	sf::Texture swordTexture;

	int facing = 0;
	float speed;

	bool interacting = false;
	bool attacking = false;
	bool flinching = false;
	bool dead = false;

	sf::Vector2f flinchDirection;

	bool wasInteractButtonPressed = false;
	bool wasAttackButtonPressed = false;

	float attackTimer = 0.0f;
	float iFrames = 0.0f;

	int hp;
	int damage;

	sf::Sound sound_swordSwing;
	sf::Sound sound_getHit;
	sf::Sound sound_death;
	sf::Sound sound_interact;

	sf::SoundBuffer buffer_swordSwing;
	sf::SoundBuffer buffer_getHit;
	sf::SoundBuffer buffer_death;
	sf::SoundBuffer buffer_interact;


public:

	Hero();
	~Hero();

	sf::Vector2f getPosition();
	sf::FloatRect getBoundingBox();
	bool isDead();
	void reset();

	void setPosition(float x, float y);
	void setDirection(int facing);
	void setSpeed(float speed);

	void update(float deltaTime, std::vector<sf::Sprite>& environment, std::vector<Npc>& npcs, std::vector<Enemy>& enemies, UI& ui);
	void draw(sf::RenderWindow& window);
};
