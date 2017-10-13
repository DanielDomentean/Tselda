#pragma once

#include <SFML/Graphics.hpp>



class UI
{

private:

	sf::Sprite healthbar;
	sf::Texture healthbarTexture;
	bool healthbarActive = true;

	sf::Sprite tutorialBox;
	sf::Texture tutorialBoxTexture;
	bool tutorialBoxActive = false;

	sf::Sprite dialogueBox;
	sf::Texture dialogueBoxTexture;
	int dialogueBoxWidth = 1200;
	int dialogueBoxHeight = 300;
	bool dialogueBoxActive = false;

	bool dialogueOptionsBoxActive = false;
	std::vector<sf::Text> dialogueOptions;

	sf::Sprite arrow;
	sf::Texture arrowTexture;
	unsigned int arrowPosition;

	sf::Text dialogue;
	sf::Font dialogueFont;

	sf::Sprite eKey;
	sf::Texture eKeyTexture;
	sf::Text eKeyText;

	sf::Sprite spaceKey;
	sf::Texture spaceKeyTexture;
	sf::Text spaceKeyText;

	sf::Sprite wasdKeys;
	sf::Texture wasdKeysTexture;
	sf::Text wasdKeysText;


public:

	UI();
	~UI();

	sf::String wrapText(sf::String string, unsigned width);

	void activateHealthbar(bool status);
	void activateTutorialBox(bool status);
	void activateDialogueBox(bool status);
	void activateDialogueOptionsBox(bool status);

	int getArrowPosition();
	void arrowUp();
	void arrowDown();

	void setDialogue(std::string dialogue);
	void setDialogueOptions(std::vector<std::string> dialogueOptions);
	void setHealth(int hearts);

	void draw(sf::RenderWindow& window);
};

