//C++ includes
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>

//SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

//My includes
#include "utils.h"
#include "camera.h"
#include "object.h"

#define PI 3.14159265359

/*
 * createWindow() -> void
 * createWindow uses a graphics settings struct to create a new window.
 */
void createWindow(sf::RenderWindow *w, struct GraphicsSettings *gs) {
	unsigned long WindowStyle;

	//Default window style.
	WindowStyle = sf::Style::Close; 

	//If fullscreen was set, we should change the style.
	if (gs->fullscreen){
		WindowStyle = sf::Style::Fullscreen;
	}

	//Create the window. herp derp.
	w->create(sf::VideoMode(gs->width, gs->height), "", WindowStyle);
	
	//Modify some settings after creation. comments.
	w->setMouseCursorVisible(true);

	//Set frame rate.
	w->setFramerateLimit(gs->frame_rate);
}

/*
 * ----------------------------------------------------------------------------
 */

int main() {
	
	//Variables used to run the game.
	sf::RenderWindow window;
	struct GraphicsSettings *gs = NULL;
	struct Controller *input = NULL;
	struct TextureNode *textures = NULL;
	Camera view;

	sf::Vector2i mousePos;
	sf::Vector2i relativeMousePos = sf::Vector2i(0, 0);
	float mouseAngle;
	int orientation;

	//Load the window settings and create a window.
	gs = loadGraphicsSettings("data/graphicsConf");
	if (gs != NULL) { 
		createWindow(&window, gs); 
	} else { 
		printf("Unrecoverable error while loading graphics settings. Exiting.\n");
		window.close();
	}

	//Load the controller settings.
	input = loadControllerConfiguration("data/controllerConf");
	if (input == NULL) { 
		printf("Unrecoverable error while loading controller settings. Exiting.\n");
		window.close();
	}

	//Start testing code ------------------------------------------------------
	loadTextureNode("data/texturedata/cow.td", &textures);
	Object testObject = Object(textures->frame_sizes[0], sf::Vector2f(0, 0), textures, sf::Vector2f(0, 0));
	view.setFocus(testObject.getCenterPointer());
	//End testing code --------------------------------------------------------

	//Our delta time counter.
	sf::Clock deltaClock;
	sf::Time dt = deltaClock.restart();

	//While the window is open, run the game.
	while (window.isOpen()) {

		//Event processing.
	    sf::Event event;
	    while (window.pollEvent(event)) {

		    //Request for closing the window.
		    if (event.type == sf::Event::Closed) {
			   window.close();
		    }
	    }

	    mousePos = sf::Mouse::getPosition(window);
	    relativeMousePos.x = mousePos.x - gs->windowCenter.x;
	    relativeMousePos.y = mousePos.y - gs->windowCenter.y;
	    mouseAngle = acos(relativeMousePos.y / magnitudeI(relativeMousePos));

	    if (relativeMousePos.x > 0.0) {
	    	orientation = ((int) ((1.0 - (mouseAngle / PI)) * 4) + 4);
	    	testObject.setOrientation(orientation);
	    } else {
	    	orientation = ((int) mouseAngle / PI * 4);
	    	testObject.setOrientation(orientation);
	    }

	    //Keyboard polling.
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key) input->up)) {

			testObject.setAnimation(1);
		} else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key) input->down)) {

			testObject.setAnimation(1);
		} else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key) input->left)) {

			testObject.setAnimation(1);
		} else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key) input->right)) {
			
			testObject.setAnimation(1);
		} else {
			//Standing
			testObject.setAnimation(0);
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key) input->escape)) {
			//ESCAPE
			window.close();
		}

		//Clear the window.
	    window.clear(sf::Color::Black);

	    //Start test code -----------------------------------------------------
	    testObject.animate(dt.asSeconds());
	    window.draw(testObject);

	    view.panToFocus(0.1f);
	    window.setView(view.getView());
	    //End test code -------------------------------------------------------

	    //Display the window and restart the delta timer.
	    window.display();
	    dt = deltaClock.restart();
	}

	//Clean up memory on closing.
	cleanUp(gs, input, textures);

	return 0;
}