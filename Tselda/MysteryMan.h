#pragma once

#include "Npc.h"



class MysteryMan : public Npc
{

public:

	MysteryMan(sf::Vector2f position);
	~MysteryMan();

	void buildDialogue(std::string dialogueID);
	void meetNpc();
};
