#include "BlueBlob.h"



/*
* CONSTRUCTOR - in here we give the enemy a texture and set up the animation. We also set some basic variables.
*/
BlueBlob::BlueBlob(sf::Texture& texture, sf::Vector2f position)
{
	// set texture and animation
	sprite.setTexture(texture);
	animation.setTexture(texture, sf::Vector2u(4, 1), 0.1f);

	// set the remaining parameters
	sprite.setPosition(position);
	hp = 6;
	damage = 1;
	speed = 100;
	aggroRange = 250;
}



/*
* DESTRUCTOR - in here we would clean up after our object has died, if needed
*/
BlueBlob::~BlueBlob()
{
}
