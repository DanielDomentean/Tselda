#include "Npc.h"



/*
* CONSTRUCTOR - in here we create our NPC by passing it a texture and setting its basic variables
*/
Npc::Npc(sf::Texture& texture, sf::Vector2f position, int numberOfFrames)
{
	// set texture and animation
	sprite.setTexture(texture);
	animation.setTexture(texture, sf::Vector2u(numberOfFrames, 1), 0.8f);

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
* GET LINE - return the requested line of dialogue
*/
std::string Npc::nextLine()
{
	std::string line = lines[currentLine];

	if (currentLine >= lines.size() - 1)
		currentLine = 0;
	else
		currentLine++;

	return line;
}



/*
* ADD LINE - add a line to our NPCs repertoire
*/
void Npc::addLine(std::string line)
{
	lines.push_back(line);
}



/*
* SET POSITION - set a new postion for the NPC
*/
void Npc::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
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
