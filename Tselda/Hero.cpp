/*
* Hero is one of the key elements of this project.
*
* It reacts to player input, controls our main charater and animates him (the "Hero") and is responsible for collision detection
*/

#include "Hero.h"



/*
* CONSTRUCTOR - in here we give our hero a texture and set up the animation. We also set some basic variables.
*/
Hero::Hero()
{
	// load our hero texture
	if (!heroTexture.loadFromFile("Resources/Sprites/Hero/Hero.png")) printf("ERROR loading HERO texture file!");

	// set texture and animation
	heroSprite.setTexture(heroTexture);
	heroAnimation.setTexture(heroTexture, sf::Vector2u(5, 4), 0.1f, 1);

	// setting up the sword
	if (!swordTexture.loadFromFile("Resources/Sprites/Hero/Sword.png")) printf("ERROR loading SWORD texture file!");
	swordSprite.setTexture(swordTexture);

	// load sound files
	if (!buffer_swordSwing.loadFromFile("Resources/Sound/Effects/sword_swing.wav")) printf("ERROR loading SWORD SWING sound file!");
	sound_swordSwing.setBuffer(buffer_swordSwing);

	if (!buffer_getHit.loadFromFile("Resources/Sound/Effects/get_hit.wav")) printf("ERROR loading GET HIT sound file!");
	sound_getHit.setBuffer(buffer_getHit);

	if (!buffer_death.loadFromFile("Resources/Sound/Effects/death.wav")) printf("ERROR loading DEATH sound file!");
	sound_death.setBuffer(buffer_death);

	if (!buffer_interact.loadFromFile("Resources/Sound/Effects/interact.wav")) printf("ERROR loading INTERACT sound file!");
	sound_interact.setBuffer(buffer_interact);

	if (!buffer_dialogueSelect.loadFromFile("Resources/Sound/Effects/select_dialogue.wav")) printf("ERROR loading DIALOGUE SELECT sound file!");
	sound_dialogueSelect.setBuffer(buffer_dialogueSelect);

	// set the remaining variables
	setDirection(DOWN);
	setSpeed(200);
	hp = 10;
	damage = 3;
}



/*
* DESTRUCTOR - in here we would clean up after our hero-object has died
*/
Hero::~Hero()
{
}



/*
* GET POSTION - returns the current position of our hero-character
*/
sf::Vector2f Hero::getPosition()
{
	return heroSprite.getPosition();
}



/*
* GET BOUNDING BOX - returns the bounding box of our hero-character
*/
sf::FloatRect Hero::getBoundingBox()
{
	return heroSprite.getGlobalBounds();
}



/*
* IS DEAD - returns true if our hero has died
*/
bool Hero::isDead()
{
	return dead;
}



/*
* RESET - reset the hero after death
*/
void Hero::reset()
{
	dead = false;
	hp = 10;
	flinching = false;
	heroSprite.setColor(sf::Color::White);
	setDirection(DOWN);
}



/*
* SET POSITION - set the position of our hero
*/
void Hero::setPosition(float x, float y)
{
	heroSprite.setPosition(x, y);
}



/*
* SET ROTATION - set the rotation of our hero
*/
void Hero::setDirection(int facing)
{
	this->facing = facing;
}



/*
* SET SPEED - set the speed of our hero
*/
void Hero::setSpeed(float speed)
{
	this->speed = speed;
}



/*
* UPDATE - this is the meat of our hero object. In this function we decide, what our hero-object will do each cycle
*/
void Hero::update(float deltaTime, std::vector<sf::Sprite>& environment, std::vector<Npc*> npcs, std::vector<Enemy>& enemies, UI& ui)
{
	sf::Vector2f movement(0.0f, 0.0f);
	sf::FloatRect intersectionRect;


	// -------------------------------------------------------> PLAYER HP AND DEATH <-------------------------------------------------------------

	ui.setHealth(hp);

	if (hp <= 0) {

		// play death sound
		sound_death.play();

		// mark as dead
		dead = true;
	}



	// ----------------------------------------------------------> PLAYER INPUT <----------------------------------------------------------------

	// Moving
	if (!interacting && !attacking) {		// && !flinching
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {	// A key is pressed - move our character left
			movement.x -= speed * deltaTime;
			facing = LEFT;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {	// D key is pressed - move our character right
			movement.x += speed * deltaTime;
			facing = RIGHT;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {	// W key is pressed - move our character up
			movement.y -= speed * deltaTime;
			facing = UP;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {	// S key is pressed - move our character down
			movement.y += speed * deltaTime;
			facing = DOWN;
		}
	}


	// Attacking
	if (!interacting) {
		bool isAttackButtonPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);	// SPACE key is pressed - attack!

																						// if key is pressed after being released
		if (isAttackButtonPressed && !wasAttackButtonPressed) {
			if (attacking == false) {
				attacking = true;

				// play attack sound
				sound_swordSwing.play();
			}
		}

		// overwrite "wasAttackButtonPressed" to be able to check if the state has changed next cycle
		wasAttackButtonPressed = isAttackButtonPressed;

		// wait for the attack animation to finish before being able to attack again
		if (attacking) {
			attackTimer += deltaTime;

			if (attackTimer > 0.3f) {	// the amount of time a sword-swing takes
				attacking = false;
				attackTimer = 0.0f;
			}
		}
	}


	// -----------------------------------------------------> NPC COLLISION DETECTION <-----------------------------------------------------------

	for (unsigned int i = 0; i < npcs.size(); i++) {

		if (heroSprite.getGlobalBounds().intersects(npcs[i]->getBoundingBox(), intersectionRect)) {

			// general movement restriction on x-axis
			if (intersectionRect.width <= intersectionRect.height && intersectionRect.height > speed * deltaTime) {

				// collision on the right
				if (getPosition().x < npcs[i]->getPosition().x && movement.x > 0) {
					movement.x = 0;
				}

				// collision on the left
				if (getPosition().x > npcs[i]->getPosition().x && movement.x < 0) {
					movement.x = 0;
				}
			}

			// general movement restriction on y-axis
			if (intersectionRect.width > intersectionRect.height && intersectionRect.width > speed * deltaTime) {

				// collision on the bottom
				if (getPosition().y < npcs[i]->getPosition().y && movement.y > 0) {
					movement.y = 0;
				}

				// collision on the top
				if (getPosition().y > npcs[i]->getPosition().y && movement.y < 0) {
					movement.y = 0;
				}
			}


			// interacting with NPCs
			bool isInteractButtonPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
			bool is_W_ButtonPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			bool is_S_ButtonPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);


			if (interacting) {

				if (npcs[i]->offersDialogueOptions()) {		// if dialogue options are available, react to one of 3 inputs

					ui.activateDialogueOptionsBox(true);
					ui.setDialogueOptions(npcs[i]->getDialogueOptions());

					// W key is pressed down after being released - move selection up
					if (is_W_ButtonPressed && !was_W_Pressed)
					{
						// selection up
						ui.arrowUp();
						sound_dialogueSelect.play();
					}

					// S key is pressed down after being release - move selection down
					if (is_S_ButtonPressed && !was_S_Pressed)
					{
						// selection down
						ui.arrowDown();
						sound_dialogueSelect.play();
					}

					// if the E key is pressed - select the dialogue option
					if (isInteractButtonPressed && !wasInteractButtonPressed)
					{
						sound_interact.play();
						int selectedOption = ui.getArrowPosition();

						// if the player chooses "leave" clean up and close the dialogue box
						if (npcs[i]->getDialogueOptions().at(selectedOption) == "- Leave -")
						{
							ui.setDialogue("");
							ui.activateDialogueBox(false);
							ui.activateDialogueOptionsBox(false);
							interacting = false;
						}
						else	// if the player chooses an answer rebuild the dialogue accordingly
						{
							ui.setDialogue(npcs[i]->getLineAt(selectedOption));

							npcs[i]->buildDialogue(npcs[i]->getDialogueOptions().at(selectedOption));
							ui.setDialogueOptions(npcs[i]->getDialogueOptions());
						}

						/*
						// get the next line
						std::string nextLine = npcs[i]->nextLine();

						// check if we reached the end of the dialogue to end the talk
						if (nextLine == "_MARKER_end_of_dialogue")
						{
							npcs[i]->resetLine();
							ui.setDialogue("");
							ui.activateDialogueBox(false);
							ui.activateDialogueOptionsBox(false);
							interacting = false;
						}
						else
						{		// if not then just show the next line
							ui.setDialogue(nextLine);
							sound_interact.play();
						}*/
					}
				}		
				else										// if no dialogue options are available, just proceed with 'E'
				{
					// if the E key is pressed
					if (isInteractButtonPressed && !wasInteractButtonPressed)
					{
						ui.setDialogue("");
						ui.activateDialogueBox(false);
						interacting = false;
					}
				}
			}
			else
			{
				// if not interacting and E Button is pressed -> start interacting
				if (isInteractButtonPressed && !wasInteractButtonPressed) {

					npcs[i]->buildDialogue("");
					ui.setDialogue(npcs[i]->getOpeningLine());
					ui.activateDialogueBox(true);
					sound_interact.play();

					interacting = true;
					npcs[i]->meetNpc();
				}
			}


			wasInteractButtonPressed = isInteractButtonPressed;
			was_W_Pressed = is_W_ButtonPressed;
			was_S_Pressed = is_S_ButtonPressed;
		}
	}


	// ----------------------------------------------------> ENEMY COLLISION DETECTION <----------------------------------------------------------

	// body collision - hero takes damage and goes into a "flinching"-state
	if (!flinching && !interacting) {
		for (unsigned int i = 0; i < enemies.size(); i++) {
			if (heroSprite.getGlobalBounds().intersects(enemies[i].getBoundingBox(), intersectionRect)) {
				if (intersectionRect.width > 10 && intersectionRect.height > 10) {
					// set flinching
					flinching = true;

					// receive damage
					hp -= enemies[i].getDamage();

					// play hit sound
					sound_getHit.play();

					// get the angle hero and enemy
					float angle = atan2(enemies[i].getPosition().y - getPosition().y, enemies[i].getPosition().x - getPosition().x);

					// set the flinching direction
					sf::Vector2f direction(std::cos(angle), std::sin(angle));
					direction = -direction;
					flinchDirection = direction;
				}
			}
		}
	}


	// while flinching the hero is invulnerable, can't move (see movement-segment) and is being pushed away from the enemy
	if (flinching) {
		iFrames += deltaTime;

		// indicate the hit with color change
		heroSprite.setColor(sf::Color(255, 70, 70, 255));

		// flinch (move in a direction roughly away from the enemy)
		movement.x = flinchDirection.x * 500 * deltaTime;
		movement.y = flinchDirection.y * 500 * deltaTime;

		// condition to stop flinching
		if (iFrames > 0.15f) {		// flinching state lasts this long
			flinching = false;
			heroSprite.setColor(sf::Color::White);
			iFrames = 0.0f;
		}
	}


	// sword collsions - enemy takes damage
	for (unsigned int i = 0; i < enemies.size(); i++) {
		if (swordSprite.getGlobalBounds().intersects(enemies[i].getBoundingBox())) {
			enemies[i].takeDamage(damage);
		}
	}


	// --------------------------------------------------> ENVIRONMENT COLLISION DETECTION <--------------------------------------------------------

	for (unsigned int i = 0; i < environment.size(); i++) {

		if (heroSprite.getGlobalBounds().intersects(environment[i].getGlobalBounds(), intersectionRect)) {

			// general movement restriction on x-axis
			if (intersectionRect.width <= intersectionRect.height && intersectionRect.height > speed * deltaTime) {		// if the intersection-rectangle is the same higher than it is wide we know we have a collision on the x-axis ("same" is included to prevent player form getting stuck)

																														// collision on the right
				if (getPosition().x < environment[i].getPosition().x && movement.x > 0) {
					movement.x = 0;
				}

				// collision on the left
				if (getPosition().x > environment[i].getPosition().x && movement.x < 0) {
					movement.x = 0;
				}
			}

			// general movement restriction on y-axis
			if (intersectionRect.width > intersectionRect.height && intersectionRect.width > speed * deltaTime) {		// if its not we have a collision on the y-axis

																														// collision on the bottom
				if (getPosition().y < environment[i].getPosition().y && movement.y > 0) {
					movement.y = 0;
				}

				// collision on the top
				if (getPosition().y > environment[i].getPosition().y && movement.y < 0) {
					movement.y = 0;
				}
			}
		}
	}


	// ------------------------------------------------------------> ANIMATION <------------------------------------------------------------------

	if (movement.x == 0 && movement.y == 0) {		// in case the player is attacking or no movement has happened set the texture (sprite-sheet) to the corresponding image (x=0) of the corresponding direction (y)

		switch (facing) {
		case DOWN:
			if (attacking) {
				heroSprite.setTextureRect(sf::IntRect(200, heroAnimation.uvRect.height * 0, heroAnimation.uvRect.width, heroAnimation.uvRect.height));
				swordSprite.setPosition(heroSprite.getPosition().x + heroAnimation.uvRect.width / 4, heroSprite.getPosition().y + heroAnimation.uvRect.height);
				swordSprite.setRotation(0);
			}
			else {
				heroSprite.setTextureRect(sf::IntRect(0, heroAnimation.uvRect.height * 0, heroAnimation.uvRect.width, heroAnimation.uvRect.height));
				swordSprite.setPosition(-100, -100);
			}
			break;
		case UP:
			if (attacking) {
				heroSprite.setTextureRect(sf::IntRect(200, heroAnimation.uvRect.height * 1, heroAnimation.uvRect.width, heroAnimation.uvRect.height));
				swordSprite.setPosition(heroSprite.getPosition().x + 3 * (heroAnimation.uvRect.width / 4), heroSprite.getPosition().y);
				swordSprite.setRotation(180);
			}
			else {
				heroSprite.setTextureRect(sf::IntRect(0, heroAnimation.uvRect.height * 1, heroAnimation.uvRect.width, heroAnimation.uvRect.height));
				swordSprite.setPosition(-100, -100);
			}
			break;
		case RIGHT:
			if (attacking) {
				heroSprite.setTextureRect(sf::IntRect(200, heroAnimation.uvRect.height * 2, heroAnimation.uvRect.width, heroAnimation.uvRect.height));
				swordSprite.setPosition(heroSprite.getPosition().x + heroAnimation.uvRect.width, heroSprite.getPosition().y + 3 * (heroAnimation.uvRect.height / 4));
				swordSprite.setRotation(270);
			}
			else {
				heroSprite.setTextureRect(sf::IntRect(0, heroAnimation.uvRect.height * 2, heroAnimation.uvRect.width, heroAnimation.uvRect.height));
				swordSprite.setPosition(-100, -100);
			}
			break;
		case LEFT:
			if (attacking) {
				heroSprite.setTextureRect(sf::IntRect(200, heroAnimation.uvRect.height * 3, heroAnimation.uvRect.width, heroAnimation.uvRect.height));
				swordSprite.setPosition(heroSprite.getPosition().x, heroSprite.getPosition().y + heroAnimation.uvRect.height / 4);
				swordSprite.setRotation(90);
			}
			else {
				heroSprite.setTextureRect(sf::IntRect(0, heroAnimation.uvRect.height * 3, heroAnimation.uvRect.width, heroAnimation.uvRect.height));
				swordSprite.setPosition(-100, -100);
			}
			break;
		}

	}
	else {		// passing everything on to executiuon
		if (!flinching) {
			heroAnimation.update(facing, deltaTime);
			heroSprite.setTextureRect(heroAnimation.uvRect);
		}

		heroSprite.move(movement);
	}
}



/*
* DRAW - get a reference to the window and draw our hero
*/
void Hero::draw(sf::RenderWindow& window)
{
	window.draw(heroSprite);

	if (attacking)
		window.draw(swordSprite);
}
