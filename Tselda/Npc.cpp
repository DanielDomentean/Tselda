#include "Npc.h"



/*
* CONSTRUCTOR - in here we create our NPC and set its basic variables. The default NPC texture is a signpost. Child-objects will overwrite it with their own texture.
*/
Npc::Npc(sf::Vector2f position)
{
	// set the position
	setPosition(position);
}



/*
* DESTRUCTOR - in here we would clean up after our NPC-object has died
*/
Npc::~Npc()
{
}



/*
* GET POSITION - return the position of our NPC
*/
sf::Vector2f Npc::getPosition()
{
	return sprite.getPosition();
}



/*
* GET BOUNDING BOX - return the bounding box of our NPC
*/
sf::FloatRect Npc::getBoundingBox()
{
	return sprite.getGlobalBounds();
}



/*
* GET OPENING LINE - returns the opening line
*/
std::string Npc::getOpeningLine()
{
	return openingLine;
}



/*
* GET LINE AT - returns the requested line of dialogue
*/
std::string Npc::getLineAt(int linePosition)
{
	return lines.at(linePosition);
}



/*
* OFFERS DIALOGUE OPTIONS - returns true if the NPC has dialogue options
*/
bool Npc::offersDialogueOptions()
{
	return hasDialogueOptions;
}



/*
* GET DIALOGUE OPTIONS
*/
std::vector<std::string> Npc::getDialogueOptions()
{
	return dialogueOptions;
}



/*
* SET OPENING LINE - set the opening line for this NPC
*/
void Npc::setOpeningLine(std::string line)
{
	openingLine = line;
}



/*
* ADD LINE - add a line to our NPCs repertoire
*/
void Npc::addLine(std::string line)
{
	lines.push_back(line);
}



/*
* ADD DIALOGUE OPTION - add a dialogue option to our NPC
*/
void Npc::addDialogueOption(std::string line)
{
	dialogueOptions.push_back(line);
}



/*
* VIRTUAL - BUILD DIALOGUE - build the dialogue for our NPC accoring to the dialogue ID
*/
void Npc::buildDialogue(std::string dialogueID)
{
}



/*
* SET POSITION - set a new postion for the NPC
*/
void Npc::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}



/*
* VIRTUAL - MEET NPC - set the global variable for this NPC
*/
void Npc::meetNpc()
{
}



/*
* UPDATE - update our NPC-object (called every cycle)
*/
void Npc::update(float deltaTime)
{
	animation.update(0, deltaTime);
	sprite.setTextureRect(animation.uvRect);
}



/*
* DRAW - get a reference to the window and draw our NPC
*/
void Npc::draw(sf::RenderWindow & window)
{
	window.draw(sprite);
}
