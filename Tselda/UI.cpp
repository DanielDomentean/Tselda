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

	// Arrow
	if (!arrowTexture.loadFromFile("Resources/Sprites/UI/Arrow.png")) printf("ERROR loading ARROW texture file!");
	arrow.setTexture(arrowTexture);
	arrowPosition = 0;

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
* WRAP TEXT - wrap the passed string if it is longer than the specified width
*/
sf::String UI::wrapText(sf::String string, unsigned width)
{
	unsigned currentOffset = 0;
	bool firstWord = true;
	std::size_t wordBegining = 0;

	for (std::size_t pos(0); pos < string.getSize(); ++pos) {
		auto currentChar = string[pos];
		if (currentChar == '\n') {
			currentOffset = 0;
			firstWord = true;
			continue;
		}
		else if (currentChar == ' ') {
			wordBegining = pos;
			firstWord = false;
		}

		auto glyph = dialogueFont.getGlyph(currentChar, 24, false);
		currentOffset += glyph.advance;

		if (!firstWord && currentOffset > width) {
			pos = wordBegining;
			string[pos] = '\n';
			firstWord = true;
			currentOffset = 0;
		}
	}

	return string;
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
	arrowPosition = 0;
}



/*
* ACTIVATE DIALOGUE OPTIONS BOX - set the status of the dialogue box
*/
void UI::activateDialogueOptionsBox(bool status)
{
	dialogueOptionsBoxActive = status;
}



/*
* GET ARROW POSITION - return the arrow position
*/
int UI::getArrowPosition()
{
	return arrowPosition;
}



/*
* ARROW UP - lower the arrow position by one
*/
void UI::arrowUp()
{
	//arrowPosition--;

	if (arrowPosition == 0)
		arrowPosition = dialogueOptions.size() - 1;
	else
		arrowPosition--;
}



/*
* ARROW DOWN - raise the arrow position by one
*/
void UI::arrowDown()
{
	//arrowPosition++;

	if (arrowPosition == dialogueOptions.size() - 1)
		arrowPosition = 0;
	else
		arrowPosition++;
}



/*
* SET DIALOGUE - pass a new string as dialogue
*/
void UI::setDialogue(std::string dialogue)
{
	this->dialogue.setString(wrapText(dialogue, dialogueBoxWidth - 50));
}



/*
* SET DIALOGUE OPTIONS - pass a vector of string to create out dialogue options
*/
void UI::setDialogueOptions(std::vector<std::string> dialogueOptions)
{
	this->dialogueOptions.clear();

	for each (std::string dialogueOption in dialogueOptions) {
		sf::Text text;

		text.setFont(dialogueFont);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);

		text.setString(wrapText(dialogueOption, dialogueBoxWidth - 50));

		this->dialogueOptions.push_back(text);
	}
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

	// Healthbar
	if (healthbarActive) {
		healthbar.setPosition(screenCenter.x - window.getSize().x / 2 + 30, screenCenter.y - window.getSize().y / 2 + 30);
		window.draw(healthbar);
	}

	// Tutorial
	if (tutorialBoxActive) {
		window.draw(tutorialBox);

		window.draw(wasdKeys);
		window.draw(spaceKey);
		window.draw(eKey);

		window.draw(wasdKeysText);
		window.draw(spaceKeyText);
		window.draw(eKeyText);
	}

	// Dialogue
	if (dialogueBoxActive) {
		dialogueBox.setPosition(screenCenter.x - dialogueBoxWidth / 2, screenCenter.y + 50);
		window.draw(dialogueBox);

		eKey.setPosition(screenCenter.x + dialogueBoxWidth / 2 - 40, dialogueBox.getPosition().y + dialogueBoxHeight - 40);
		window.draw(eKey);

		dialogue.setPosition(dialogueBox.getPosition().x + 30, dialogueBox.getPosition().y + 30);
		window.draw(dialogue);
	}
	else {
		eKey.setPosition(1445, 3690);
	}

	// Answers
	if (dialogueOptionsBoxActive) {

		// the answers
		for (unsigned int i = 0; i < dialogueOptions.size(); i++) {
			dialogueOptions[i].setPosition(dialogueBox.getPosition().x + 120, dialogueBox.getPosition().y + 165 + i*50);
			window.draw(dialogueOptions[i]);
		}

		// the arrow
		arrow.setPosition(dialogueBox.getPosition().x + 70, dialogueBox.getPosition().y + 150 + (arrowPosition * 50));
		window.draw(arrow);
	}
}
