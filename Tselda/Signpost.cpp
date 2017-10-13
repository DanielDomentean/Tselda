#include "Signpost.h"



/*
* CONSTRUCTOR - in here we create our SINGPOST and set its basic variables
*/
Signpost::Signpost(sf::Vector2f position, std::string text) : Npc(position)
{
	// load our texture
	if (!texture.loadFromFile("Resources/Sprites/NPCs/Signpost.png")) printf("ERROR loading SIGNPOST texture file!");

	// set texture and animation
	sprite.setTexture(texture);
	animation.setTexture(texture, sf::Vector2u(1, 1), 0.8f);

	// set dialogue options
	hasDialogueOptions = false;

	// set the opening line
	setOpeningLine(text);
}



/*
* DESTRUCTOR - in here we would clean up after our NPC-object has died
*/
Signpost::~Signpost()
{
}
