#pragma once

#include "Animation.h"



class Npc
{

private:

	sf::Sprite sprite;
	sf::Texture texture;
	Animation animation;

	std::vector<std::string> lines;
	unsigned int currentLine = 0;


public:

	Npc(sf::Texture& texture, sf::Vector2f position, int numberOfFrames);
	~Npc();

	sf::Vector2f getPosition();
	sf::FloatRect getBoundingBox();
	std::string nextLine();

	void addLine(std::string);
	void setPosition(sf::Vector2f position);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
};
