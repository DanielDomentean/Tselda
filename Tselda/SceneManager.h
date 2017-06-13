#pragma once

#include <SFML/Audio.hpp>

#include "Hero.h"
#include "Door.h"
#include "Npc.h"
#include "UI.h"
#include "BlueBlob.h"
#include "RedBlob.h"
#include "Tektite.h"
#include "Objective.h"

#include <fstream>
#include <sstream>



class SceneManager
{

private:

	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	sf::Color clearColor;

	std::vector<sf::Sprite> environment;
	std::vector<sf::Sprite> ground;
	std::vector<Door> doors;
	std::vector<Npc> npcs;
	std::vector<Enemy> enemies;
	sf::FloatRect tutorialTrigger;

	std::vector<sf::Texture> environmentTextures;
	std::vector<sf::Texture> npcTextures;
	std::vector<sf::Texture> enemyTextures;

	sf::Texture poofTexture;
	sf::SoundBuffer buffer_enemyHitSound;

	Objective objective_beach;
	Objective objective_mountain;
	Objective objective_forest;

	sf::Texture portalTexture;
	Objective portal;

	Hero hero;
	UI ui;

	bool loading = false;
	bool playingCredits = false;
	float elapsedTime = 0.0f;

	sf::Music music;


public:

	// constants
	const static int OVERWORLD = 0;
	const static int HOUSE = 1;
	const static int DUNGEON = 2;
	const static int CREDITS = 3;

	SceneManager(int level, sf::Vector2f position);
	~SceneManager();

	std::vector<sf::Sprite> getObjects();

	void draw(sf::RenderWindow& window, sf::View& camera);
	void loadLevel(int level, sf::Vector2f position);
	void update(float elapsedTime);
};
