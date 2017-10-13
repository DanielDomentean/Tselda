#pragma once

#include "Npc.h"



class Signpost :public Npc
{

public:

	Signpost(sf::Vector2f position, std::string text);
	~Signpost();
};
