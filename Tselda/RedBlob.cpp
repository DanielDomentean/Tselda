#include "RedBlob.h"



/*
* CONSTRUCTOR - in here we give the enemy a texture and set up the animation. We also set some basic variables.
*/
RedBlob::RedBlob(sf::Texture& texture, sf::Vector2f position)
{
	// set texture and animation
	sprite.setTexture(texture);
	animation.setTexture(texture, sf::Vector2u(4, 1), 0.1f);

	// set the remaining parameters
	sprite.setPosition(position);
	hp = 9;
	damage = 2;
	speed = 120;
	aggroRange = 250;
}



/*
* DESTRUCTOR - in here we would clean up after our object has died, if needed
*/
RedBlob::~RedBlob()
{
}
