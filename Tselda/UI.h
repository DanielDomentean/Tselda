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
	int dialogueBoxWidth = 880;
	int dialogueBoxHeight = 220;
	bool dialogueBoxActive = false;

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

	void activateHealthbar(bool status);
	void activateTutorialBox(bool status);
	void activateDialogueBox(bool status);

	void setDialogue(std::string dialogue);
	void setHealth(int hearts);

	void draw(sf::RenderWindow& window);
};

