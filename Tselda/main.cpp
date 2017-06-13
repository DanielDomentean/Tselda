#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "SceneManager.h"



int main()
{
	// set up the basic stuff
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Tselda");
	sf::View camera(sf::Vector2f(0, 0), sf::Vector2f(1280, 720));
	float elapsedTime = 0.0f;
	sf::Clock clock;


	// initializing the world
	SceneManager sceneManager(SceneManager::OVERWORLD, sf::Vector2f(1700, 3810));


	// run the program as long as the window is open
	while (window.isOpen())
	{
		// first get the delta time (time elapsed)
		elapsedTime = clock.restart().asSeconds();

		// event handling
		sf::Event event;
		while (window.pollEvent(event)) {

			switch (event.type) {

				// close the window
			case sf::Event::Closed:
				window.close();
				break;

				// resize the window
			case sf::Event::Resized:
				camera.setSize((float)event.size.width, (float)event.size.height);
				break;
			}
		}

		// Update the level (and in it the rest of our objects)
		sceneManager.update(elapsedTime);

		// draw the level (and with it everything else)
		sceneManager.draw(window, camera);

		// display our render window
		window.display();
	}


	return 0;
}
