#pragma once

#include <SFML/Graphics.hpp>



class Animation
{

private:

	sf::Vector2u imageDimensions;	// for example 5 images by 7 images (5*7) - hence a vector
	sf::Vector2u currentImage;		// the coordinates of the current image

	float elapsedTime;				// the time elapsed between cycles
	float timePerFrame;				// the time each frame gets

	int specialAnimation;			// added later: the amount of columns at the end of the sprite sheet that are not part of the main-animation. Used here for the attack-frame.
	bool hasSpecial = false;
	bool onlyPlayOnce = false;
	bool donePlaying = false;


public:

	sf::IntRect uvRect;

	Animation();
	~Animation();

	bool hasSpecialAnimation();

	void setTexture(sf::Texture texture, sf::Vector2u imageDimensions, float timePerFrame);
	void setTexture(sf::Texture texture, sf::Vector2u imageDimensions, float timePerFrame, int specialAnimation);
	void setTexture(sf::Texture texture, sf::Vector2u imageDimensions, float timePerFrame, bool onlyPlayOnce);

	void update(int row, float deltaTime);
	bool animationDone();
};