#pragma once

#include "Npc.h"



class Shopkeeper : public Npc
{

public:

	Shopkeeper(sf::Vector2f position);
	~Shopkeeper();

	void buildDialogue(std::string dialogueID);
	void meetNpc();
};
