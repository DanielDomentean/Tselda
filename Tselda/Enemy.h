#pragma once

#include <SFML/Audio.hpp>
#include "Animation.h"



class Enemy
{

protected:

	sf::Sprite sprite;
	sf::Texture texture;
	Animation animation;
	sf::Sprite poof;
	Animation poofAnimation;

	std::vector<sf::Vector2f> waypoints;
	sf::Vector2f currentWaypoint;
	unsigned int currentWaypointNumber = 0;

	int hp;
	int damage;
	int speed;
	int aggroRange;

	bool moving = false;
	bool flinching = false;
	bool dying = false;
	bool dead = false;

	float iFrames = 0.0f;
	float waitTime = 0.0f;

	sf::Sound sound_getHit;


public:

	Enemy();
	~Enemy();

	sf::Vector2f getPosition();
	sf::FloatRect getBoundingBox();
	sf::Vector2f nextWaypoint();
	bool isDead();

	void setPosition(sf::Vector2f position);
	void addWaypoint(sf::Vector2f position);
	void setDeathAnimation(sf::Texture& texture);
	void setHitSound(sf::SoundBuffer& soundBuffer);

	void update(float elapsedTime, sf::FloatRect heroPosition);
	void draw(sf::RenderWindow& window);

	void takeDamage(int damage);
	int getDamage();
};
