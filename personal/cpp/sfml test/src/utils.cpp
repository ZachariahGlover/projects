//C++ includes
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <math.h>

#include "utils.h"

/*
 * loadGraphicsSettings(const char *) -> *GraphicsSettings
 * loadGraphicsSettings reads settings from a file filename into a structure.
 * Returns a pointer to the new graphics configuration structure.
 */
struct GraphicsSettings *loadGraphicsSettings(const char *filename) {

	struct GraphicsSettings *gs = new GraphicsSettings;

	if (gs != NULL) {

		//Creates an input stream from the settings file
		std::ifstream settingsFile(filename);
	    std::string line;

	    //Loop while there are lines to read.
	    while (getline(settingsFile, line)) {

	        std::istringstream lineData(line.substr(line.find("=") + 1));

	        //Conditions to load and set each parameter.
	        if (line.find("frame_rate") != (size_t) -1) {
	        	lineData >> gs->frame_rate;
		 	} else if (line.find("fullscreen") != (size_t) -1) {
	        	lineData >> gs->fullscreen;
		 	} else if (line.find("width") != (size_t) -1) {
	            lineData >> gs->width;
	        } else if (line.find("height") != (size_t) -1) {
	            lineData >> gs->height;
	        }

	        //Error handling. Sets defaults if we fail.
	        if (lineData.fail()) {
	        	printf("Error configuring screen. Setting defaults.\n");
	        	gs->fullscreen = 0;
	        	gs->width = 1024;
	        	gs->height = 576;
	        	break;
	        }
	    }

	    //If fullscreen is set, we change the screen resolution to match the
	    //desktop resolution. I guess this isn't typical but why would you
	    //want to play at a lower resolution? Weirdo.
	    if (gs->fullscreen) {
	    	sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	    	gs->width = vm.width;
	    	gs->height = vm.height;
	    }

	    gs->windowCenter = sf::Vector2i(gs->width/2, gs->height/2);

	    return gs;

	} else {
		printf("Failed to allocate memory for graphics configuration.\n");
		return NULL;
	}
}

/*
 * loadControllerConfiguration() -> *Controller
 * loadControllerConfiguration reads settings from a file filename.
 * Returns a pointer to the controller struct that the settings are loaded
 * into.
 */
struct Controller *loadControllerConfiguration(const char *filename) {

	struct Controller *cc = new Controller;

	if (cc != NULL) {

		//Creates an input stream from the settings file
		std::ifstream settingsFile(filename);
	    std::string line;

	    //Loop while there are lines to read.
	    while (getline(settingsFile, line)) {

	        std::istringstream lineData(line.substr(line.find("=") + 1));

	        //Conditions to load and set each parameter.
	        if (line.find("escape") != (size_t) -1) {
	            lineData >> cc->escape;
	        } else if (line.find("up") != (size_t) -1) {
            	lineData >> cc->up;
	        } else if (line.find("down") != (size_t) -1) {
	            lineData >> cc->down;
	        } else if (line.find("left") != (size_t) -1) {
	            lineData >> cc->left;
	        } else if (line.find("right") != (size_t) -1) {
	            lineData >> cc->right;
	        }

	        //Error handling. Sets defaults if we fail.
        	if (lineData.fail()) {
        		printf("Error configuring controller. Setting defaults.\n");
        		cc->up = 22;
				cc->down = 18;
				cc->left = 0;
				cc->right = 3;
        		break;
        	}
	    }

	    return cc;

	} else {
		printf("Failed to allocate memory for controller configuration.\n");
		return NULL;
	}
}

/*
 * loadTexture(const char * , *Texture) -> int
 * Loads an image from filename into the texture pointed to by *texture.
 * Returns an int to indicate success.
 */
int loadTexture(const char *filename, sf::Texture *texture) {
	
	//Load the texture from a file and return our success indicator.
	if (texture->loadFromFile(filename)) {
	    return 1;
	}
	return 0;
}

/*
 * loadTextureNode(const char *, **TextureNode) -> *TextureNode
 * Loads a set of textures described in filename.
 * The textures are loaded into a texture node and added to the front of the
 * linked list of texture nodes pointed to by texture_list.
 * Returns a pointer to the texture node that was added to the list.
 * (slightly redundant, I know)
 */
struct TextureNode *loadTextureNode(const char *filename, TextureNode **texture_list) {

	//Creates an input stream from the settings file
	std::ifstream skinFile(filename);
    std::string line;

    //Allocate space for the new texture node.
    TextureNode *texture_node = new TextureNode;
    strcpy(texture_node->filename, filename);

    //Get the first line.
    getline(skinFile, line);
    std::istringstream lineData(line.substr(line.find("=") + 1));

    //The first line should be the number of animation sheets to load.
    if (line.find("num_animations") != (size_t) -1) {
    	lineData >> texture_node->num_animations;

    	//Allocate space to hold the texture node's data.
    	texture_node->textures = new sf::Texture *[texture_node->num_animations];
    	texture_node->num_orientations = new int[texture_node->num_animations];
    	texture_node->num_frames = new int[texture_node->num_animations];
    	texture_node->frame_sizes = new sf::Vector2f[texture_node->num_animations];

    	//For each animation we have to load the same data.
    	for (int i = 0; i < texture_node->num_animations; i++) {

    		//Load the sprite sheet.
    		getline(skinFile, line);
    		lineData.str((line.substr(line.find("=") + 1)));
    		const char * texture_filename = lineData.str().c_str();
    		texture_node->textures[i] = new sf::Texture;
            if (!(loadTexture(texture_filename, texture_node->textures[i]))) {
            	delete texture_node;
	 			return NULL;
	 		}

	 		//Load the number of frames.
	 		getline(skinFile, line);
	 		lineData.clear();
    		lineData.str((line.substr(line.find("=") + 1)));
    		lineData >> texture_node->num_frames[i];

    		//Load the number of orientations.
    		getline(skinFile, line);
    		lineData.clear();
    		lineData.str((line.substr(line.find("=") + 1)));
    		lineData >> texture_node->num_orientations[i];

    		//Load the frame sizes.
    		getline(skinFile, line);
    		lineData.clear();
    		lineData.str((line.substr(line.find("=") + 1)));
    		lineData >> texture_node->frame_sizes[i].x;
    		getline(skinFile, line);
    		lineData.clear();
    		lineData.str((line.substr(line.find("=") + 1)));
    		lineData >> texture_node->frame_sizes[i].y;
    	}

    	//Error handling. There's no default so we fail.
        if (lineData.fail()) {
        	delete texture_node;
 			return NULL;
        }

    } else {
    	delete texture_node;
    	return NULL;
    }

    //Add the new texture node to the front of the texture list.
    if (*texture_list == NULL) {
    	*texture_list = texture_node;
    } else {
    	texture_node->next = *texture_list;
    	*texture_list = texture_node;
    }

    return texture_node;
}

/*
 * cleanUp(GraphicsSettings *, Controller *, TextureNode *) -> void
 * Clean up frees the dynamic memory we allocated to run certain aspects of the game.
 */
void cleanUp(struct GraphicsSettings *gs, struct Controller *input, struct TextureNode *textures) {
	
	//Delete the graphics settings.
	if (gs != NULL) {
		delete gs;
	}

	//Delete the input settings.
	if (input != NULL) {
		delete input;
	}

	//Delete the textures.
	if (textures != NULL) {
		struct TextureNode *t0, *t1;
		t0 = textures;
		while (t0->next != NULL) {
			t1 = t0->next;
			delete t0;
			t0 = t1;
		}
	}
}

//Vector functions.
float dotProductI(sf::Vector2i a, sf::Vector2i b) {
	return ((a.x * b.x) + (a.y * b.y));
}
float dotProductF(sf::Vector2f a, sf::Vector2f b) {
	return ((a.x * b.x) + (a.y * b.y));
}

float magnitudeI(sf::Vector2i a) {
	return sqrt(pow(a.x, 2.0) + pow(a.y, 2.0));
}
float magnitudeF(sf::Vector2f a) {
	return sqrt(pow(a.x, 2.0) + pow(a.y, 2.0));
}
