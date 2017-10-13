#pragma once

#include "Animation.h"
#include "Globals.h"



class Npc
{

protected:

	sf::Sprite sprite;
	sf::Texture texture;
	Animation animation;

	std::string openingLine;
	std::vector<std::string> lines;
	std::vector<std::string> dialogueOptions;

	bool hasDialogueOptions;
	unsigned int currentLine = 0;


public:

	Npc(sf::Vector2f position);
	~Npc();

	sf::Vector2f getPosition();
	sf::FloatRect getBoundingBox();

	std::string getOpeningLine();
	std::string getLineAt(int linePosition);
	std::vector<std::string> getDialogueOptions();
	bool offersDialogueOptions();

	void setOpeningLine(std::string);
	void addLine(std::string line);
	void addDialogueOption(std::string line);
	virtual void buildDialogue(std::string dialogueID);

	void setPosition(sf::Vector2f position);
	virtual void meetNpc();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
};
