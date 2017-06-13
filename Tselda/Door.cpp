#include "Door.h"



/*
* CONSTRUCTOR
*/
Door::Door(sf::Sprite sprite, int destination, sf::Vector2f desinationPosition)
{
	this->sprite = sprite;
	this->destination = destination;
	this->destinationPosition = desinationPosition;
}



/*
* DESTRUCTOR - in here we would clean up after our hero-object has died
*/
Door::~Door()
{
}



/*
* GET BOUNDING BOX - return the bounding box of the door-sprite
*/
sf::FloatRect Door::getBoundingBox()
{
	return sprite.getGlobalBounds();
}



/*
* GET DESTINATION - return the destination identifier of the door
*/
int Door::getDestination()
{
	return destination;
}



/*
* GET DESTINATION POSITION - return the position our hero will have within the new destination
*/
sf::Vector2f Door::getDestinationPosition()
{
	return destinationPosition;
}
