#pragma once

#include "Enemy.h"



class BlueBlob : public Enemy
{

public:

	BlueBlob(sf::Texture& texture, sf::Vector2f position);
	~BlueBlob();
};
