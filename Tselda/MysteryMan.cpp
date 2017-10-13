#include "MysteryMan.h"



/*
* CONSTRUCTOR - in here we create our MYSTERY MAN and set its basic variables
*/
MysteryMan::MysteryMan(sf::Vector2f position) : Npc(position)
{
	// load our texture
	if (!texture.loadFromFile("Resources/Sprites/NPCs/MysteryMan.png")) printf("ERROR loading MYSTERY MAN texture file!");

	// set texture and animation
	sprite.setTexture(texture);
	animation.setTexture(texture, sf::Vector2u(1, 1), 0.8f);

	// because the default dialogue with the ID ""
	buildDialogue("");
}



/*
* DESTRUCTOR - in here we would clean up after our NPC-object has died
*/
MysteryMan::~MysteryMan()
{
}



/*
* BUILD DIALOGUE - build the dialogue for our NPC accoring to the dialogue ID
*/
void MysteryMan::buildDialogue(std::string dialogueID)
{
	

	// build dialogue according to NPC-state
	if (GLOBAL_objective_beach_done && GLOBAL_objective_mountain_done && GLOBAL_objective_forest_done)
	{
		// clear all containers
		lines.clear();
		dialogueOptions.clear();

		// set dialogue options
		hasDialogueOptions = false;

		// set the opening line
		setOpeningLine("Ahh! You have found them all! The day I've been waiting for so long has come: Our creators name shall finally be revealed.\n\nPrepare to meet your fate!");
		setPosition(sf::Vector2f(325, 300));
	}
	else
	{
		// ---------- MEETING FOR THE FIRST TIME ----------
		if (!GLOBAL_mysteryManMet && dialogueID == "")
		{
			// clear all containers
			lines.clear();
			dialogueOptions.clear();

			// set dialogue options
			hasDialogueOptions = true;

			// set the opening line
			setOpeningLine("Njee-hee-hee! What do mine eyes spy? A hero?");

			// add dialogue options
			addDialogueOption("And who might you be?");
			addDialogueOption("Can you tell me what I am supposed to do on this island?");
			addDialogueOption("- Leave -");

			// add the lines
			addLine("*sigh*\nI am but a fool waiting for a day that will never come . . .");
			addLine("I expect you are looking for the secret of the island. Well, come back when you found the three magical triangles.\nHu-hu-hu!");
		}


		// ---------- COMING BACK ----------
		if (GLOBAL_mysteryManMet && dialogueID == "")
		{
			// clear all containers
			lines.clear();
			dialogueOptions.clear();

			// set dialogue options
			hasDialogueOptions = true;

			// set the opening line
			setOpeningLine("Njee-hee-hee! I've been expecting your return.");

			// add dialogue options
			addDialogueOption("Who are you again?");
			addDialogueOption("What was it again, that I should do?");
			addDialogueOption("- Leave -");

			// add the lines
			addLine("*sigh*\nI am but a fool waiting for a day that will never come . . .");
			addLine("Find the magical triangles, then return to my cave.\nHu-hu-hu!");
		}
	}
}



/*
* MEET NPC - set the global variable for this NPC
*/
void MysteryMan::meetNpc()
{
	GLOBAL_mysteryManMet = true;
}
