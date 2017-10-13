#pragma once

#include "Npc.h"



class OldMan : public Npc
{

public:

	OldMan(sf::Vector2f position);
	~OldMan();

	void buildDialogue(std::string dialogueID);
	void meetNpc();
};
