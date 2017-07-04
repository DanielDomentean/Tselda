#include "Objective.h"



/*
 * CONSTRUCTOR - in here we set up our objective, give it a sprite and a position
 */
Objective::Objective()
{
	// load our hero texture
	if (!texture.loadFromFile("Resources/Sprites/Objectives/Trigon.png")) printf("ERROR loading TRIGON texture file!");

	// set texture and animation
	sprite.setTexture(texture);
	animation.setTexture(texture, sf::Vector2u(13, 1), 0.07f);

	if (!buffer_pick_up.loadFromFile("Resources/Sound/Effects/objective_pickup.wav")) printf("ERROR loading OBJECTIVE PICKUP sound file!");
	sound_pick_up.setBuffer(buffer_pick_up);

	// set the position
	sprite.setPosition(0, 0);
}



/*
 * DESTRUCTOR - in here we would clean up after our object has died, if needed
 */
Objective::~Objective()
{
}



/*
 * SET POSITION - set a new postion for the NPC
 */
void Objective::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}



/*
 * SET TEXTURE - in case we want another texture than the default trigon
 */
void Objective::setTexture(sf::Texture & texture, int numberOfFrames)
{
	// set texture and animation
	sprite.setTexture(texture);
	animation.setTexture(texture, sf::Vector2u(numberOfFrames, 1), 0.07f);
}



/*
 * SET TEXTURE - in case we want another texture than the default trigon
 */
void Objective::setStatus(bool status)
{
	done = status;
}



/*
 * GET SPRITE - return the sprite of our objective (this can be used to make to objective into something more i.e. a door or an enemy)
 */
sf::Sprite Objective::getSprite()
{
	return sprite;
}



/*
 * IS DONE - returns to us the status of this objective
 */
bool Objective::isDone()
{
	return done;
}



/*
 * UPDATE - we run this every cycle
 */
void Objective::update(float deltaTime, sf::FloatRect heroBoundingBox)
{
	sf::FloatRect intersectionRect;

	animation.update(0, deltaTime);
	sprite.setTextureRect(animation.uvRect);

	if (sprite.getGlobalBounds().intersects(heroBoundingBox, intersectionRect)) {
		if (intersectionRect.width > 10 && intersectionRect.height > 10) {
			sound_pick_up.play();
			done = true;
		}
	}
}



/*
 * DRAW - pass our objective on to the window so it can be drawn
 */
void Objective::draw(sf::RenderWindow & window)
{
	window.draw(sprite);
}
