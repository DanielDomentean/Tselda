#include "OldMan.h"



/*
* CONSTRUCTOR - in here we create our OLD MAN and set its basic variables
*/
OldMan::OldMan(sf::Vector2f position) : Npc(position)
{
	// load our texture
	if (!texture.loadFromFile("Resources/Sprites/NPCs/OldMan.png")) printf("ERROR loading OLD MAN texture file!");

	// set texture and animation
	sprite.setTexture(texture);
	animation.setTexture(texture, sf::Vector2u(2, 1), 0.8f);

	// because the default dialogue with the ID ""
	buildDialogue("");
}



/*
* DESTRUCTOR - in here we would clean up after our NPC-object has died
*/
OldMan::~OldMan()
{
}



/*
* BUILD DIALOGUE - build the dialogue for our NPC accoring to the dialogue ID
*/
void OldMan::buildDialogue(std::string dialogueID)
{
	// ---------- UNFRIENDLY DIALOGUE - MEETING FIRST TIME ----------
	if (!GLOBAL_oldManMet && !GLOBAL_oldManFriendly && dialogueID == "")
	{
		// clear all containers
		lines.clear();
		dialogueOptions.clear();

		// set dialogue options
		hasDialogueOptions = true;

		// set the opening line
		setOpeningLine("Greetings, young hero! I am an old man. We are often used in these games to provide giudance and wisdom. However, today is my free day  -  so bugger off!");

		// add dialogue options
		addDialogueOption("YOU bugger off!");
		addDialogueOption("I'm just looking for some help");
		addDialogueOption("- Leave -");

		// add the lines
		addLine("Don't make me get my stick . . .");
		addLine("*sigh* Alright, alright, but don't make it too long.");
	}


	// ---------- UNFRIENDLY DIALOGUE - RETURNING ----------
	if (GLOBAL_oldManMet && !GLOBAL_oldManFriendly && dialogueID == "")
	{
		// clear all containers
		lines.clear();
		dialogueOptions.clear();

		// set dialogue options
		hasDialogueOptions = true;

		// set the opening line
		setOpeningLine("You again! Bugger off I said!");

		// add dialogue options
		addDialogueOption("YOU bugger off!");
		addDialogueOption("I'm just looking for some help");
		addDialogueOption("- Leave -");

		// add the lines
		addLine("Don't make me get my stick . . .");
		addLine("*sigh* Alright, alright, but don't make it too long.");
	}


			// ---------- Im just looking for some help ----------
			if (!GLOBAL_oldManFriendly && dialogueID == "I'm just looking for some help")
			{
				GLOBAL_oldManFriendly = true;

				// clear all containers
				lines.clear();
				dialogueOptions.clear();

				// set dialogue options
				hasDialogueOptions = true;

				// add dialogue options
				addDialogueOption("Whats my mission?");
				addDialogueOption("Anything else?");
				addDialogueOption("- Leave -");

				// add the lines
				addLine("As far as I know there are three magical thingamajiggies on this Island. All the heroes coming past here always keep talking about those . . . I think I saw one of them washed up on the beach.");
				addLine("It's dangerous to go alone - take th . . . Wait, why did I just say that?");
			}


	// ---------- FRIENDLY DIALOGUE ----------
	if (GLOBAL_oldManFriendly && dialogueID == "")
	{
		// clear all containers
		lines.clear();
		dialogueOptions.clear();

		// set dialogue options
		hasDialogueOptions = true;

		// set the opening line
		setOpeningLine("Greetings, young hero!");

		// add dialogue options
		addDialogueOption("Whats my mission?");
		addDialogueOption("Anything else?");
		addDialogueOption("- Leave -");

		// add the lines
		addLine("As far as I know there are three magical thingamajiggies on this Island. All the heroes coming past here always keep talking about those . . . I think I saw one of them washed up on the beach.");
		addLine("It's dangerous to go alone - take th . . . Wait, why did I just say that?");
	}
}



/*
* MEET NPC - set the global variable for this NPC
*/
void OldMan::meetNpc()
{
	GLOBAL_oldManMet = true;
}
