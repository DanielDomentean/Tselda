#pragma once

#include "Enemy.h"



class Tektite : public Enemy
{

public:

	Tektite(sf::Texture& texture, sf::Vector2f position);
	~Tektite();
};
