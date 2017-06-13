#pragma once

#include "Enemy.h"



class RedBlob : public Enemy
{

public:

	RedBlob(sf::Texture& texture, sf::Vector2f position);
	~RedBlob();
};

