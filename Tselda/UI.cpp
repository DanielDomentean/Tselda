#include "UI.h"



/*
* CONSTRUCTOR - in here we load all the textures and set up all our sprites for use
*/
UI::UI()
{
	// Healthbar
	if (!healthbarTexture.loadFromFile("Resources/Sprites/UI/Heart.png")) printf("ERROR loading HEART texture file!");
	healthbarTexture.setRepeated(true);
	healthbar.setTexture(healthbarTexture);

	// Tutorial box
	if (!tutorialBoxTexture.loadFromFile("Resources/Sprites/UI/Tutorial_Background.png")) printf("ERROR loading TUTORIAL BACKGROUND texture file!");
	tutorialBox.setTexture(tutorialBoxTexture);
	tutorialBox.setPosition(1100, 3500);

	// Dialogue box
	if (!dialogueBoxTexture.loadFromFile("Resources/Sprites/UI/UI_Black.png")) printf("ERROR loading UI BLACK texture file!");
	dialogueBox.setTextureRect(sf::IntRect(0, 0, dialogueBoxWidth, dialogueBoxHeight));
	dialogueBox.setTexture(dialogueBoxTexture);

	// Dialogue text
	if (!dialogueFont.loadFromFile("Resources/Sprites/UI/Fonts/Minecraftia-Regular.ttf")) printf("ERROR loading font file!");
	dialogue.setFont(dialogueFont);
	dialogue.setCharacterSize(24);
	dialogue.setFillColor(sf::Color::White);

	// E Key
	if (!eKeyTexture.loadFromFile("Resources/Sprites/UI/E_Key.png")) printf("ERROR loading E KEY texture file!");
	eKey.setTexture(eKeyTexture);
	eKey.setPosition(1445, 3690);

	eKeyText.setFont(dialogueFont);
	eKeyText.setCharacterSize(24);
	eKeyText.setFillColor(sf::Color::White);
	eKeyText.setString("Interact");
	eKeyText.setPosition(1400, 3770);

	// Space Key
	if (!spaceKeyTexture.loadFromFile("Resources/Sprites/UI/Space_Key.png")) printf("ERROR loading SPACE KEY texture file!");
	spaceKey.setTexture(spaceKeyTexture);
	spaceKey.setPosition(1300, 3890);

	spaceKeyText.setFont(dialogueFont);
	spaceKeyText.setCharacterSize(24);
	spaceKeyText.setFillColor(sf::Color::White);
	spaceKeyText.setString("Attack");
	spaceKeyText.setPosition(1305, 3970);

	// WASD Keys
	if (!wasdKeysTexture.loadFromFile("Resources/Sprites/UI/WASD_Keys.png")) printf("ERROR loading WASD KEYS texture file!");
	wasdKeys.setTexture(wasdKeysTexture);
	wasdKeys.setPosition(1195, 3670);

	wasdKeysText.setFont(dialogueFont);
	wasdKeysText.setCharacterSize(24);
	wasdKeysText.setFillColor(sf::Color::White);
	wasdKeysText.setString("Move");
	wasdKeysText.setPosition(1205, 3770);
}



/*
* DESTRUCTOR - in here we would clean up after our UI-object has died, if needed
*/
UI::~UI()
{
}



/*
* ACTIVATE HEALTHBAR - set the status of the healthbar
*/
void UI::activateHealthbar(bool status)
{
	healthbarActive = status;
}



/*
* ACTIVATE TUTORIAL BOX - set the status of the tutorial box
*/
void UI::activateTutorialBox(bool status)
{
	tutorialBoxActive = status;
}



/*
* ACTIVATE DIALOGUE BOX - set the status of the dialogue box
*/
void UI::activateDialogueBox(bool status)
{
	dialogueBoxActive = status;
}



/*
* SET DIALOGUE - pass a new string as dialogue
*/
void UI::setDialogue(std::string dialogue)
{
	this->dialogue.setString(dialogue);
}



/*
* SET HEALTH - pass a new value for the healthbar
*/
void UI::setHealth(int hearts)
{
	int heartsConverted = hearts * 25;
	healthbar.setTextureRect(sf::IntRect(0, 0, heartsConverted, 25));
}



/*
* DRAW - get a reference to the window and draw our UI
*/
void UI::draw(sf::RenderWindow& window)
{
	sf::Vector2f screenCenter = window.getView().getCenter();

	if (healthbarActive) {
		healthbar.setPosition(screenCenter.x - window.getSize().x / 2 + 30, screenCenter.y - window.getSize().y / 2 + 30);
		window.draw(healthbar);
	}

	if (tutorialBoxActive) {
		window.draw(tutorialBox);

		window.draw(wasdKeys);
		window.draw(spaceKey);
		window.draw(eKey);

		window.draw(wasdKeysText);
		window.draw(spaceKeyText);
		window.draw(eKeyText);
	}

	if (dialogueBoxActive) {
		dialogueBox.setPosition(screenCenter.x - dialogueBoxWidth / 2, screenCenter.y + 50);
		window.draw(dialogueBox);

		eKey.setPosition(screenCenter.x + dialogueBoxWidth / 2 - 40, dialogueBox.getPosition().y + dialogueBoxHeight - 20);
		window.draw(eKey);

		dialogue.setPosition(dialogueBox.getPosition().x + 30, dialogueBox.getPosition().y + 40);
		window.draw(dialogue);
	}
	else {
		eKey.setPosition(1445, 3690);
	}
}
