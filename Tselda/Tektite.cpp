#include "Tektite.h"



/*
* CONSTRUCTOR - in here we give the enemy a texture and set up the animation. We also set some basic variables.
*/
Tektite::Tektite(sf::Texture& texture, sf::Vector2f position)
{
	// set texture and animation
	sprite.setTexture(texture);
	animation.setTexture(texture, sf::Vector2u(2, 1), 0.1f, 1);

	// set the remaining parameters
	sprite.setPosition(position);
	hp = 6;
	damage = 1;
	speed = 250;
	aggroRange = 300;
}



/*
* DESTRUCTOR - in here we would clean up after our object has died, if needed
*/
Tektite::~Tektite()
{
}
