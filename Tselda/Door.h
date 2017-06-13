#pragma once

#include "SFML\Graphics.hpp"



class Door
{

private:

	sf::Sprite sprite;
	int destination;
	sf::Vector2f destinationPosition;


public:

	Door(sf::Sprite sprite, int destination, sf::Vector2f desinationPosition);
	~Door();

	sf::FloatRect getBoundingBox();
	int getDestination();
	sf::Vector2f getDestinationPosition();
};

