#include "Animation.h"



/*
* CONSTRUCTOR - just setting some basic variables
*/
Animation::Animation()
{
	elapsedTime = 0.0f;
	currentImage.x = 0;
	currentImage.y = 0;
	specialAnimation = 0;
}



/*
* DESTRUCTOR - in here we would clean up after our Animation-object has died, if needed
*/
Animation::~Animation()
{
}



/*
* HAS SPECIAL ANIMATION - returns true if entity has a special animation
*/
bool Animation::hasSpecialAnimation()
{
	return hasSpecial;
}



/*
* SET TEXTURE - we use this function to pass a texture (internally a pointer) to our animation and tell it the dimensions
*/
void Animation::setTexture(sf::Texture texture, sf::Vector2u imageDimensions, float timePerFrame)
{
	this->imageDimensions = imageDimensions;
	this->timePerFrame = timePerFrame;

	uvRect.width = texture.getSize().x / imageDimensions.x;
	uvRect.height = texture.getSize().y / imageDimensions.y;
}



/*
* SET TEXTURE - we use this function to pass a texture (internally a pointer) to our animation and tell it the dimensions
*/
void Animation::setTexture(sf::Texture texture, sf::Vector2u imageDimensions, float timePerFrame, int specialAnimation)
{
	this->imageDimensions = imageDimensions;
	this->timePerFrame = timePerFrame;
	this->specialAnimation = specialAnimation;

	if (specialAnimation > 0)
		hasSpecial = true;

	uvRect.width = texture.getSize().x / imageDimensions.x;
	uvRect.height = texture.getSize().y / imageDimensions.y;
}



/*
* SET TEXTURE - we use this function to pass a texture (internally a pointer) to our animation and tell it the dimensions
*/
void Animation::setTexture(sf::Texture texture, sf::Vector2u imageDimensions, float timePerFrame, bool onlyPlayOnce)
{
	this->imageDimensions = imageDimensions;
	this->timePerFrame = timePerFrame;
	this->onlyPlayOnce = onlyPlayOnce;

	uvRect.width = texture.getSize().x / imageDimensions.x;
	uvRect.height = texture.getSize().y / imageDimensions.y;
}



/*
* UPDATE - this is where the actual animation happens. We set the texture-rect based on the time that passed.
*/
void Animation::update(int row, float deltaTime)
{
	if (!donePlaying) {

		currentImage.y = row;
		elapsedTime += deltaTime;

		// if the elapsed time is bigger than the time we want to give each frame, switch to the next frame
		if (elapsedTime >= timePerFrame) {
			currentImage.x++;
			elapsedTime = 0.0f;
		}

		// if the framecount for that row has reached the end, reset it
		if (currentImage.x >= imageDimensions.x - specialAnimation)
			if (onlyPlayOnce)
				donePlaying = true;
			else
				currentImage.x = 0;

		// actually move the rect to the right position of the sprite-sheet (texture)
		uvRect.top = currentImage.y * uvRect.height;
		uvRect.left = currentImage.x * uvRect.width;
	}
}



/*
* ANIMATION DONE - returns if a play-once-animation is done or not
*/
bool Animation::animationDone()
{
	return donePlaying;
}
