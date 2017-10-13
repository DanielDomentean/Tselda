/*
* Scene Manager was originally named Level and operates similar to a "Room" in GameMaker.
* Since the functionality changed a little bit the name was apdated as well to reflect those changes.
*
* Next to "Hero", the SceneManager is basically the key element of this project. It loads textures, coordinates, sound files and creates sprites to populate the world with.
* It also contains the main functions for updating our game every cycle and drawing to the render window.
*/

#include "SceneManager.h"



/*
* CONSTRUCTOR - in here we just set up a few basics and call "loadLevel". Having this constructor saves us calling load level after creating a object.
*/
SceneManager::SceneManager(int level, sf::Vector2f position)
{
	// load the poof texture
	if (!poofTexture.loadFromFile("Resources/Sprites/Enemies/Poof.png")) printf("ERROR loading POOF texture file!");

	// load the enemy hit sound
	if (!buffer_enemyHitSound.loadFromFile("Resources/Sound/Effects/enemy_get_hit.wav")) printf("ERROR loading ENEMY GET HIT sound file!");

	// make the music loop
	music.setLoop(true);

	// load the level
	loadLevel(level, position);
}



/*
* DESTRUCTOR - in here we would clean up after our SceneManager has died, if needed
*/
SceneManager::~SceneManager()
{
	for each (Npc* npc in npcs)
	{
		delete npc;
	}
}



/*
* GET OBJECTS - returns a list of all regular objects (mostly environment)
*/
std::vector<sf::Sprite> SceneManager::getObjects()
{
	return environment;
}



/*
* DRAW - draw everything within the level to our RenderWindow. The order of things is very important here, as this basically is our rendering pipeline.
*/
void SceneManager::draw(sf::RenderWindow& window, sf::View& camera)
{
	if (!loading) {

		// clear color
		window.clear(clearColor);

		// background
		window.draw(backgroundSprite);

		if (!portal.isDone()) {

			// ground (non collision objects)
			for (unsigned int i = 0; i < ground.size(); i++)
				window.draw(ground[i]);

			// environment (collision objects)
			for (unsigned int i = 0; i < environment.size(); i++)
				window.draw(environment[i]);

			//  npcs
			for (unsigned int i = 0; i < npcs.size(); i++)
				npcs[i]->draw(window);

			// enemies
			for (unsigned int i = 0; i < enemies.size(); i++)
				enemies[i].draw(window);

			// objectives
			if (!GLOBAL_objective_beach_done)
				objective_beach.draw(window);

			if (!GLOBAL_objective_mountain_done)
				objective_mountain.draw(window);

			if (!GLOBAL_objective_forest_done)
				objective_forest.draw(window);

			if (GLOBAL_objective_beach_done && GLOBAL_objective_mountain_done && GLOBAL_objective_forest_done && !portal.isDone())
				portal.draw(window);

			// hero
			hero.draw(window);

			// set the camera
			camera.setCenter(hero.getPosition().x + 25, hero.getPosition().y + 25);
			window.setView(camera);

			// UI and dialog
			ui.draw(window);
		}

	} else {

		// clear with black
		window.clear();
	}
}



/*
* LOAD LEVEL - this function loads a new level and is also called upon initialization of the SceneManager-object.
*/
void SceneManager::loadLevel(int level, sf::Vector2f position)
{
	// start loading screen
	loading = true;


	// empty all containers
	environment.clear();
	doors.clear();
	npcs.clear();
	enemies.clear();

	environmentTextures.clear();
	enemyTextures.clear();


	// place objectives far out the screen - so we dont have to destroy them, but we also are never confronted with them
	objective_beach.setPosition(-10000, -10000);
	objective_mountain.setPosition(-10000, -10000);
	objective_forest.setPosition(-10000, -10000);
	portal.setPosition(-10000, -10000);


	// stop the music
	music.stop();


	// Set the hero's postion
	hero.setPosition(position.x, position.y);


	// Create the world
	// -------------------------------------------------------------------------- OVERWORLD --------------------------------------------------------------------------
	if (level == OVERWORLD) {

		// set the new background
		if (!backgroundTexture.loadFromFile("Resources/Sprites/Environment/Overworld/Background_Overworld.png")) printf("ERROR loading OVERWORLD BACKGROUND texture file!");
		backgroundSprite.setTexture(backgroundTexture, true);

		// set the clearcolor
		clearColor = sf::Color(46, 49, 146, 255);	// Color of the sea


		// loading textures
		sf::Texture invisibleTexture;
		if (!invisibleTexture.loadFromFile("Resources/Sprites/Environment/Invisible_Wall.png")) printf("ERROR loading INVISIBLE WALL texture file!");
		invisibleTexture.setRepeated(true);
		environmentTextures.push_back(invisibleTexture);

		sf::Texture treeTexture;
		if (!treeTexture.loadFromFile("Resources/Sprites/Environment/Overworld/Tree.png")) printf("ERROR loading TREE texture file!");
		treeTexture.setRepeated(true);
		environmentTextures.push_back(treeTexture);

		sf::Texture rock_1Texture;
		if (!rock_1Texture.loadFromFile("Resources/Sprites/Environment/Overworld/Rock_1.png")) printf("ERROR loading ROCK 1 texture file!");
		rock_1Texture.setRepeated(true);
		environmentTextures.push_back(rock_1Texture);

		sf::Texture rock_2Texture;
		if (!rock_2Texture.loadFromFile("Resources/Sprites/Environment/Overworld/Rock_2.png")) printf("ERROR loading ROCK 2 texture file!");
		rock_2Texture.setRepeated(true);
		environmentTextures.push_back(rock_2Texture);

		sf::Texture bushTexture;
		if (!bushTexture.loadFromFile("Resources/Sprites/Environment/Overworld/Bush.png")) printf("ERROR loading BUSH texture file!");
		bushTexture.setRepeated(true);
		environmentTextures.push_back(bushTexture);

		sf::Texture houseRoofTexture;
		if (!houseRoofTexture.loadFromFile("Resources/Sprites/Environment/Overworld/House_Roof.png")) printf("ERROR loading HOUSE ROOF texture file!");
		houseRoofTexture.setRepeated(true);
		environmentTextures.push_back(houseRoofTexture);

		sf::Texture houseWallTexture;
		if (!houseWallTexture.loadFromFile("Resources/Sprites/Environment/Overworld/House_Wall.png")) printf("ERROR loading HOUSE WALL texture file!");
		houseWallTexture.setRepeated(true);
		environmentTextures.push_back(houseWallTexture);

		sf::Texture houseDoorTexture;
		if (!houseDoorTexture.loadFromFile("Resources/Sprites/Environment/Overworld/House_Door.png")) printf("ERROR loading HOUSE DOOR texture file!");
		houseDoorTexture.setRepeated(true);
		environmentTextures.push_back(houseDoorTexture);

		sf::Texture rockEntranceTexture;
		if (!rockEntranceTexture.loadFromFile("Resources/Sprites/Environment/Overworld/Rock_entrance.png")) printf("ERROR loading ROCK ENTRANCE texture file!");
		rockEntranceTexture.setRepeated(true);
		environmentTextures.push_back(rockEntranceTexture);


		// setting up input file stream
		std::ifstream coordinates("Resources/Sprites/Environment/Overworld/Coords_Overworld.txt");
		std::string currentLine;

		// go through the file line by line to copy objects into the main object array and non-collision objects into their array
		while (std::getline(coordinates, currentLine)) {

			// if the entry is a regular object
			if (currentLine[0] == 'O') {

				// setting up necessary variables
				std::istringstream iss(currentLine);
				char type, name, comma;
				float x, y;
				int width, height;

				// error-checking
				if (!(iss >> type >> name >> x >> y >> comma >> width >> height)) { break; }

				// creating objects
				sf::Sprite newObject;

				switch (name) {
				case 'I':
					newObject.setTexture(environmentTextures[0]);
					break;
				case 'T':
					newObject.setTexture(environmentTextures[1]);
					break;
				case 'R':
					newObject.setTexture(environmentTextures[2]);
					break;
				case 'S':
					newObject.setTexture(environmentTextures[3]);
					break;
				case 'B':
					newObject.setTexture(environmentTextures[4]);
					break;
				case 'H':
					newObject.setTexture(environmentTextures[5]);
					break;
				case 'W':
					newObject.setTexture(environmentTextures[6]);
					break;
				case 'D':
					newObject.setTexture(environmentTextures[7]);
					break;
				case 'E':
					newObject.setTexture(environmentTextures[8]);
					break;
				}

				newObject.setPosition(x, y);
				newObject.setTextureRect(sf::IntRect(0, 0, width, height));

				environment.push_back(newObject);
			}


			// if the entry is a non-collision (ground) object
			if (currentLine[0] == 'N') {
			}
		}


		// Populate the world with NPCs
		npcs.push_back(new OldMan(sf::Vector2f(4200, 2590)));		// add the Old Man
		npcs.push_back(new Shopkeeper(sf::Vector2f(4070, 2590)));	// add the Shopkeeper
		npcs.push_back(new Signpost(sf::Vector2f(2940, 2240), "\n East: Old Man's House \n\n West: Forbidden Woods \n\n South: Hero's Rest"));	// add a signpost


		// Populate the world with enemies
		sf::Texture blueBlobTexture;
		if (!blueBlobTexture.loadFromFile("Resources/Sprites/Enemies/BlueBlob.png")) printf("ERROR loading BLUE BLOB texture file!");
		enemyTextures.push_back(blueBlobTexture);

		sf::Texture redBlobTexture;
		if (!redBlobTexture.loadFromFile("Resources/Sprites/Enemies/RedBlob.png")) printf("ERROR loading RED BLOB texture file!");
		enemyTextures.push_back(redBlobTexture);

		sf::Texture tektiteTexture;
		if (!tektiteTexture.loadFromFile("Resources/Sprites/Enemies/Tektite.png")) printf("ERROR loading TEKTITE texture file!");
		enemyTextures.push_back(tektiteTexture);

		// BLUE BLOBS
		BlueBlob blue_1(enemyTextures[0], sf::Vector2f(2292, 3054));
		blue_1.addWaypoint(sf::Vector2f(2283, 2988));
		blue_1.addWaypoint(sf::Vector2f(2190, 3095));
		blue_1.addWaypoint(sf::Vector2f(2378, 3095));
		enemies.push_back(blue_1);

		BlueBlob blue_2(enemyTextures[0], sf::Vector2f(2793, 2991));
		blue_2.addWaypoint(sf::Vector2f(2738, 3037));
		blue_2.addWaypoint(sf::Vector2f(2829, 2923));
		enemies.push_back(blue_2);

		BlueBlob blue_3(enemyTextures[0], sf::Vector2f(3265, 2300));
		blue_3.addWaypoint(sf::Vector2f(3056, 2300));
		blue_3.addWaypoint(sf::Vector2f(3365, 2300));
		enemies.push_back(blue_3);

		BlueBlob blue_4(enemyTextures[0], sf::Vector2f(3223, 3468));
		blue_4.addWaypoint(sf::Vector2f(3195, 3246));
		blue_4.addWaypoint(sf::Vector2f(3134, 3599));
		blue_4.addWaypoint(sf::Vector2f(3400, 3472));
		blue_4.addWaypoint(sf::Vector2f(3333, 3333));
		enemies.push_back(blue_4);

		BlueBlob blue_5(enemyTextures[0], sf::Vector2f(4808, 3471));
		enemies.push_back(blue_5);

		BlueBlob blue_6(enemyTextures[0], sf::Vector2f(4968, 3349));
		enemies.push_back(blue_6);

		BlueBlob blue_7(enemyTextures[0], sf::Vector2f(1398, 2525));
		enemies.push_back(blue_7);

		BlueBlob blue_8(enemyTextures[0], sf::Vector2f(1068, 2426));
		blue_8.addWaypoint(sf::Vector2f(1280, 2433));
		blue_8.addWaypoint(sf::Vector2f(1068, 2426));
		enemies.push_back(blue_8);

		// RED BLOBS
		RedBlob red_1(enemyTextures[1], sf::Vector2f(4743, 3334));
		enemies.push_back(red_1);

		RedBlob red_2(enemyTextures[1], sf::Vector2f(2950, 1300));
		red_2.addWaypoint(sf::Vector2f(2850, 1460));
		red_2.addWaypoint(sf::Vector2f(2627, 1475));
		red_2.addWaypoint(sf::Vector2f(2850, 1460));
		red_2.addWaypoint(sf::Vector2f(2950, 1300));
		enemies.push_back(red_2);

		RedBlob red_3(enemyTextures[1], sf::Vector2f(1900, 2430));
		enemies.push_back(red_3);

		RedBlob red_4(enemyTextures[1], sf::Vector2f(581, 3193));
		red_4.addWaypoint(sf::Vector2f(750, 3193));
		red_4.addWaypoint(sf::Vector2f(581, 3193));
		enemies.push_back(red_4);

		RedBlob red_5(enemyTextures[1], sf::Vector2f(750, 3500));
		red_5.addWaypoint(sf::Vector2f(540, 3500));
		red_5.addWaypoint(sf::Vector2f(750, 3500));
		enemies.push_back(red_5);

		RedBlob red_6(enemyTextures[1], sf::Vector2f(880, 3333));
		enemies.push_back(red_6);

		// TEKTITES
		Tektite tektite_1(enemyTextures[2], sf::Vector2f(4627, 1500));
		enemies.push_back(tektite_1);

		Tektite tektite_2(enemyTextures[2], sf::Vector2f(4400, 1400));
		enemies.push_back(tektite_2);

		Tektite tektite_3(enemyTextures[2], sf::Vector2f(4100, 1600));
		enemies.push_back(tektite_3);

		Tektite tektite_4(enemyTextures[2], sf::Vector2f(4000, 1420));
		enemies.push_back(tektite_4);

		Tektite tektite_5(enemyTextures[2], sf::Vector2f(3800, 1650));
		enemies.push_back(tektite_5);

		Tektite tektite_6(enemyTextures[2], sf::Vector2f(3600, 1400));
		enemies.push_back(tektite_6);

		Tektite tektite_7(enemyTextures[2], sf::Vector2f(3000, 1600));
		enemies.push_back(tektite_7);

		Tektite tektite_8(enemyTextures[2], sf::Vector2f(3200, 925));
		enemies.push_back(tektite_8);

		// after all enemies are created give them all a death animation - this can also be done individually, but since we only have one death-animation we're doing it for all in a loop
		for (unsigned int i = 0; i < enemies.size(); i++)
			enemies[i].setDeathAnimation(poofTexture);

		// after all enemies are created give them all a hit sound - this can also be done individually, but since we only have one hit sound we're doing it for all in a loop
		for (unsigned int i = 0; i < enemies.size(); i++)
			enemies[i].setHitSound(buffer_enemyHitSound);


		// Set up doors to other worlds
		sf::Sprite houseDoorSprite;
		houseDoorSprite.setPosition(4095, 2510);
		houseDoorSprite.setTextureRect(sf::IntRect(0, 0, 110, 40));
		Door houseDoor(houseDoorSprite, SceneManager::HOUSE, sf::Vector2f(225, 225));
		doors.push_back(houseDoor);

		sf::Sprite dungeonDoorSprite;
		dungeonDoorSprite.setPosition(2100, 1100);
		dungeonDoorSprite.setTextureRect(sf::IntRect(0, 0, 300, 50));
		Door dungeonDoor(dungeonDoorSprite, SceneManager::DUNGEON, sf::Vector2f(325, 450));
		doors.push_back(dungeonDoor);


		// put objectives in the world
		if (!GLOBAL_objective_beach_done)
			objective_beach.setPosition(5020, 3530);

		if (!GLOBAL_objective_mountain_done)
			objective_mountain.setPosition(3285, 820);

		if (!GLOBAL_objective_forest_done)
			objective_forest.setPosition(230, 4370);


		// Tutorial setup
		tutorialTrigger.left = 1600;
		tutorialTrigger.top = 3700;
		tutorialTrigger.width = 250;
		tutorialTrigger.height = 300;


		// start the music
		if (!music.openFromFile("Resources/Sound/Music/Music_Overworld.wav")) printf("ERROR loading OVERWORLD MUSIC sound file!");
		music.play();
	}


	// ---------------------------------------------------------------------------- HOUSE ----------------------------------------------------------------------------
	if (level == HOUSE) {

		// set the new background
		if (!backgroundTexture.loadFromFile("Resources/Sprites/Environment/House/Background_House.png")) printf("ERROR loading HOUSE BACKGROUND texture file!");
		backgroundSprite.setTexture(backgroundTexture, true);

		// set the clearcolor
		clearColor = sf::Color(0, 0, 0, 255);	// Black


		// loading textures
		sf::Texture invisibleTexture;
		if (!invisibleTexture.loadFromFile("Resources/Sprites/Environment/Invisible_Wall.png")) printf("ERROR loading INVISIBLE WALL texture file!");
		invisibleTexture.setRepeated(true);
		environmentTextures.push_back(invisibleTexture);

		sf::Texture wallTexture;
		if (!wallTexture.loadFromFile("Resources/Sprites/Environment/House/Wall.png")) printf("ERROR loading WALL texture file!");
		wallTexture.setRepeated(true);
		environmentTextures.push_back(wallTexture);

		sf::Texture bedTexture;
		if (!bedTexture.loadFromFile("Resources/Sprites/Environment/House/Bed.png")) printf("ERROR loading BED texture file!");
		bedTexture.setRepeated(true);
		environmentTextures.push_back(bedTexture);;

		sf::Texture shelfTexture;
		if (!shelfTexture.loadFromFile("Resources/Sprites/Environment/House/Shelf.png")) printf("ERROR loading SHELF texture file!");
		shelfTexture.setRepeated(true);
		environmentTextures.push_back(shelfTexture);

		sf::Texture fireplaceTexture;
		if (!fireplaceTexture.loadFromFile("Resources/Sprites/Environment/House/Fireplace.png")) printf("ERROR loading FIREPLACE texture file!");
		fireplaceTexture.setRepeated(true);
		environmentTextures.push_back(fireplaceTexture);

		sf::Texture tableTexture;
		if (!tableTexture.loadFromFile("Resources/Sprites/Environment/House/Table.png")) printf("ERROR loading TABLE texture file!");
		tableTexture.setRepeated(true);
		environmentTextures.push_back(tableTexture);


		// setting up input file stream
		std::ifstream coordinates("Resources/Sprites/Environment/House/Coords_House.txt");
		std::string currentLine;

		// go through the file line by line to copy objects into the main object array and non-collision objects into their array
		while (std::getline(coordinates, currentLine)) {

			// if the entry is a regular object
			if (currentLine[0] == 'O') {

				// setting up necessary variables
				std::istringstream iss(currentLine);
				char type, name, comma;
				float x, y;
				int width, height;

				// error-checking
				if (!(iss >> type >> name >> x >> y >> comma >> width >> height)) { break; }

				// creating objects
				sf::Sprite newObject;

				switch (name) {
				case 'I':
					newObject.setTexture(environmentTextures[0]);
					break;
				case 'W':
					newObject.setTexture(environmentTextures[1]);
					break;
				case 'B':
					newObject.setTexture(environmentTextures[2]);
					break;
				case 'S':
					newObject.setTexture(environmentTextures[3]);
					break;
				case 'F':
					newObject.setTexture(environmentTextures[4]);
					break;
				case 'T':
					newObject.setTexture(environmentTextures[5]);
					break;
				}

				newObject.setPosition(x, y);
				newObject.setTextureRect(sf::IntRect(0, 0, width, height));

				environment.push_back(newObject);
			}


			// if the entry is a non-collision (ground) object
			if (currentLine[0] == 'N') {
			}
		}


		// Set up doors to other worlds
		sf::Sprite outsideDoorSprite;
		outsideDoorSprite.setPosition(200, 310);
		outsideDoorSprite.setTextureRect(sf::IntRect(0, 0, 100, 50));
		Door outsideDoor(outsideDoorSprite, SceneManager::OVERWORLD, sf::Vector2f(4125, 2600));
		doors.push_back(outsideDoor);


		// start the music
		if (!music.openFromFile("Resources/Sound/Music/Music_House.wav")) printf("ERROR loading HOUSE MUSIC sound file!");
		music.play();
	}


	// --------------------------------------------------------------------------- DUNGEON -------------------------------------------------------------------------
	if (level == DUNGEON) {

		// set the new background
		if (!backgroundTexture.loadFromFile("Resources/Sprites/Environment/Dungeon/Background_Dungeon.png")) printf("ERROR loading DUNGEON BACKGROUND texture file!");
		backgroundSprite.setTexture(backgroundTexture, true);

		// set the clearcolor
		clearColor = sf::Color(0, 0, 0, 255);	// Black


		// loading textures
		sf::Texture invisibleTexture;
		if (!invisibleTexture.loadFromFile("Resources/Sprites/Environment/Invisible_Wall.png")) printf("ERROR loading INVISIBLE WALL texture file!");
		invisibleTexture.setRepeated(true);
		environmentTextures.push_back(invisibleTexture);

		sf::Texture wallTexture;
		if (!wallTexture.loadFromFile("Resources/Sprites/Environment/Dungeon/DungeonWall.png")) printf("ERROR loading DUNGEON WALL texture file!");
		wallTexture.setRepeated(true);
		environmentTextures.push_back(wallTexture);

		sf::Texture blockTexture;
		if (!blockTexture.loadFromFile("Resources/Sprites/Environment/Dungeon/Block.png")) printf("ERROR loading BLOCK texture file!");
		blockTexture.setRepeated(true);
		environmentTextures.push_back(blockTexture);

		sf::Texture rubbleTexture;
		if (!rubbleTexture.loadFromFile("Resources/Sprites/Environment/Dungeon/Rubble.png")) printf("ERROR loading RUBBLE texture file!");
		rubbleTexture.setRepeated(true);
		environmentTextures.push_back(rubbleTexture);

		if (!portalTexture.loadFromFile("Resources/Sprites/Objectives/Portal.png")) printf("ERROR loading PORTAL texture file!");
		portal.setTexture(portalTexture, 6);



		// setting up input file stream
		std::ifstream coordinates("Resources/Sprites/Environment/Dungeon/Coords_Dungeon.txt");
		std::string currentLine;

		// go through the file line by line to copy objects into the main object array and non-collision objects into their array
		while (std::getline(coordinates, currentLine)) {

			// if the entry is a regular object
			if (currentLine[0] == 'O') {

				// setting up necessary variables
				std::istringstream iss(currentLine);
				char type, name, comma;
				float x, y;
				int width, height;

				// error-checking
				if (!(iss >> type >> name >> x >> y >> comma >> width >> height)) { break; }

				// creating objects
				sf::Sprite newObject;

				switch (name) {
				case 'I':
					newObject.setTexture(environmentTextures[0]);
					break;
				case 'W':
					newObject.setTexture(environmentTextures[1]);
					break;
				case 'B':
					newObject.setTexture(environmentTextures[2]);
					break;
				case 'R':
					newObject.setTexture(environmentTextures[3]);
					break;
				}

				newObject.setPosition(x, y);
				newObject.setTextureRect(sf::IntRect(0, 0, width, height));

				environment.push_back(newObject);
			}


			// if the entry is a non-collision (ground) object
			if (currentLine[0] == 'N') {
			}
		}


		// Populate the world with NPCs

		// add the Mystery Man
		npcs.push_back(new MysteryMan(sf::Vector2f(325, 100)));


		// Set up doors to other worlds
		sf::Sprite outsideDoorSprite;
		outsideDoorSprite.setPosition(300, 510);
		outsideDoorSprite.setTextureRect(sf::IntRect(0, 0, 100, 50));
		Door outsideDoor(outsideDoorSprite, SceneManager::OVERWORLD, sf::Vector2f(2225, 1200));
		doors.push_back(outsideDoor);


		// put objectives in the world
		if (GLOBAL_objective_beach_done && GLOBAL_objective_mountain_done && GLOBAL_objective_forest_done) {
			portal.setPosition(325, 125);
		}


		// start the music
		if (!music.openFromFile("Resources/Sound/Music/Music_Dungeon.wav")) printf("ERROR loading DUNGEON MUSIC sound file!");
		music.play();
	}


	// --------------------------------------------------------------------------- CREDITS -------------------------------------------------------------------------
	if (level == CREDITS) {

		// set the new background
		if (!backgroundTexture.loadFromFile("Resources/Sprites/UI/Credits.png")) printf("ERROR loading CREDITS texture file!");
		backgroundSprite.setTexture(backgroundTexture, true);

		// set the clearcolor
		clearColor = sf::Color(0, 0, 0, 255);	// Black


		// set the game-status to "playing credits"
		playingCredits = true;


		// start the music
		if (!music.openFromFile("Resources/Sound/Music/Music_Dungeon.wav")) printf("ERROR loading DUNGEON MUSIC sound file!");
		music.play();
	}
}



/*
* UPDATE - this update-function is called every cycle of the game. In fact we use the SceneManager update funciton to call all the other update funcitons, as all other entities can only exist within "SceneManager".
*/
void SceneManager::update(float elapsedTime)
{
	if (!portal.isDone()) {

		// check for hero death
		if (hero.isDead()) {
			hero.reset();
			loadLevel(SceneManager::OVERWORLD, sf::Vector2f(1710, 3810));
		}


		// check for door-collisions and load a new level if necesarry
		for (unsigned int i = 0; i < doors.size(); i++)
			if (hero.getBoundingBox().intersects(doors[i].getBoundingBox()))
				loadLevel(doors[i].getDestination(), doors[i].getDestinationPosition());


		// update the enemies for death movement and animation
		for (unsigned int i = 0; i < enemies.size(); i++)
			if (enemies[i].isDead())
				enemies.erase(enemies.begin() + i);
			else
				enemies[i].update(elapsedTime, hero.getBoundingBox());


		// update NPCs for movement and animation
		for (unsigned int i = 0; i < npcs.size(); i++)
			npcs[i]->update(elapsedTime);


		// update the hero for movement and animation
		if (!loading)
			hero.update(elapsedTime, environment, npcs, enemies, ui);


		// setting the global objectives
		if (objective_beach.isDone())
			GLOBAL_objective_beach_done = true;

		if (objective_mountain.isDone())
			GLOBAL_objective_mountain_done = true;

		if (objective_forest.isDone())
			GLOBAL_objective_forest_done = true;

		// update objectives for movement and animation
		if (!GLOBAL_objective_beach_done)
			objective_beach.update(elapsedTime, hero.getBoundingBox());

		if (!GLOBAL_objective_mountain_done)
			objective_mountain.update(elapsedTime, hero.getBoundingBox());

		if (!GLOBAL_objective_forest_done)
			objective_forest.update(elapsedTime, hero.getBoundingBox());

		portal.update(elapsedTime, hero.getBoundingBox());


		// check for tutorial display
		if (hero.getBoundingBox().intersects(tutorialTrigger))
			ui.activateTutorialBox(true);
		else
			ui.activateTutorialBox(false);


	} else {


		// play the credits
		if (!playingCredits)
			loadLevel(SceneManager::CREDITS, sf::Vector2f(0, 0));
		else
			if (backgroundSprite.getPosition().y >= -3280) {
				backgroundSprite.move(0, -100 * elapsedTime);
			}
	}


	// display loading screen for 2 seconds for each load --- this can be animated later (i.e. fade in/out or curtain-effect)
	if (loading) {
		this->elapsedTime += elapsedTime;

		if (this->elapsedTime >= 2.0f) {
			this->elapsedTime = 0.0f;
			loading = false;
		}
	}
}
