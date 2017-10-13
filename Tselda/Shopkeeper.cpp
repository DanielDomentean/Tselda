#include "Shopkeeper.h"



/*
* CONSTRUCTOR - in here we create our SHOPKEEPER and set its basic variables
*/
Shopkeeper::Shopkeeper(sf::Vector2f position) : Npc(position)
{
	// load our texture
	if (!texture.loadFromFile("Resources/Sprites/NPCs/Shopkeeper.png")) printf("ERROR loading SHOPKEEPER texture file!");

	// set texture and animation
	sprite.setTexture(texture);
	animation.setTexture(texture, sf::Vector2u(2, 1), 0.8f);

	// because the default dialogue with the ID ""
	buildDialogue("");
}



/*
* DESTRUCTOR - in here we would clean up after our NPC-object has died
*/
Shopkeeper::~Shopkeeper()
{
}



/*
* BUILD DIALOGUE - build the dialogue for our NPC accoring to the dialogue ID
*/
void Shopkeeper::buildDialogue(std::string dialogueID)
{
	// ---------- MEETING FOR THE FIRST TIME ----------
	if (!GLOBAL_shopkeeperMet && dialogueID == "")
	{
		// clear all containers
		lines.clear();
		dialogueOptions.clear();

		// set dialogue options
		hasDialogueOptions = true;

		// set the opening line
		setOpeningLine("Greetings Hero! Got sumthin that might intrest ya!");

		// add dialogue options
		addDialogueOption("Show me your weapons.");
		addDialogueOption("I would like to see some armor.");
		addDialogueOption("- Leave -");

		// add the lines
		addLine("So you are the aggressive kind? I’m not judging. What’s your preference?");
		addLine("Defense is the best offense, right? No wait, that sounds wrong . . . Anyhow, what do you like?");
	}


	// ---------- COMING BACK ----------
	if (GLOBAL_shopkeeperMet && dialogueID == "" || dialogueID == "What else ya got?")
	{
		// clear all containers
		lines.clear();
		dialogueOptions.clear();

		// set dialogue options
		hasDialogueOptions = true;

		// set the opening line
		setOpeningLine("Welcome back! Whadda ya buyin?");

		// add dialogue options
		addDialogueOption("Show me your weapons.");
		addDialogueOption("I would like to see some armor.");
		addDialogueOption("- Leave -");

		// add the lines
		addLine("So you are the aggressive kind? I’m not judging. What’s your preference?");
		addLine("Defense is the best offense, right? No wait, that sounds wrong . . . Anyhow, what do you like?");
	}


			// ---------- Show me your weapons ----------
			if (dialogueID == "Show me your weapons." || dialogueID == "Nah")
			{
				// clear all containers
				lines.clear();
				dialogueOptions.clear();

				// set dialogue options
				hasDialogueOptions = true;

				// add dialogue options
				addDialogueOption("Master-Sword");
				addDialogueOption("A stick");
				addDialogueOption("What else ya got?");

				// add the lines
				addLine("The legendary blade, that banishes all evil. A weapon for a true hero!");
				addLine("What's brown and sticky? - this thing!");
				addLine("What else? It only weapons or armor here matey!");
			}


			// ---------- I would like to see some armor ----------
			if (dialogueID == "I would like to see some armor." || dialogueID == "Nope")
			{
				// clear all containers
				lines.clear();
				dialogueOptions.clear();

				// set dialogue options
				hasDialogueOptions = true;

				// add dialogue options
				addDialogueOption("Legendary Golden Armor");
				addDialogueOption("A bucket with a leather strap");
				addDialogueOption("What else ya got?");

				// add the lines
				addLine("This Legendary armor is said to be forged by the godess herself!");
				addLine("I made it myself! Very proud of this one.");
				addLine("What else? It only weapons or armor here matey!");
			}


					// ---------- BUYING WEAPONS ----------
					if (dialogueID == "Master-Sword" || dialogueID == "A stick")
					{
						// clear all containers
						lines.clear();
						dialogueOptions.clear();

						// set dialogue options
						hasDialogueOptions = true;

						// add dialogue options
						addDialogueOption("I want it!");
						addDialogueOption("Nah");

						// add the lines
						addLine("I would love to sell it to you, but unfortunately you have no inventory . . .");
						addLine("Somethign else maybe?");
					}


					// ---------- BUYING ARMOR ----------
					if (dialogueID == "Legendary Golden Armor" || dialogueID == "A bucket with a leather strap")
					{
						// clear all containers
						lines.clear();
						dialogueOptions.clear();

						// set dialogue options
						hasDialogueOptions = true;

						// add dialogue options
						addDialogueOption("Yes, I'll take it!");
						addDialogueOption("Nope");

						// add the lines
						addLine("This transaction would be a lot easier if this game had an inventory-system . . .");
						addLine("Try something else.");
					}
}



/*
* MEET NPC - set the global variable for this NPC
*/
void Shopkeeper::meetNpc()
{
	GLOBAL_shopkeeperMet = true;
}
