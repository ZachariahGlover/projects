#ifndef __utils_header
#define __utils_header

#include <SFML/Graphics.hpp>

//Structure to hold window configuration settings.
struct GraphicsSettings {
	int frame_rate;
	int fullscreen;
	int width;
	int height;
	sf::Vector2i windowCenter;
};

//Structure to hold user input settings.
struct Controller {
	int escape;
	int up;
	int down;
	int left;
	int right;
};

//Structure to store texture data.
struct TextureNode {
	char filename[64];
	int num_animations;

	sf::Texture **textures;

	int *num_orientations;
	int *num_frames;
	sf::Vector2f *frame_sizes;

	TextureNode *next;

	//A default constructor for texture nodes.
	TextureNode() {
		num_animations = -1;
		textures = NULL;
		num_orientations = NULL;
		num_frames = NULL;
		frame_sizes = NULL;
		next = NULL;
	}

	//A destructor for texture nodes.
	~TextureNode() {
		if (textures != NULL) {
			delete[] textures;
		}
		if (num_orientations != NULL) {
			delete num_orientations;
		}
		if (num_frames != NULL) {
			delete num_frames;
		}
		if (frame_sizes != NULL) {
			delete frame_sizes;
		}
	}
};

struct GraphicsSettings *loadGraphicsSettings(const char *filename);
struct Controller *loadControllerConfiguration(const char *filename);

int loadTexture(const char *filename, sf::Texture *texture);
struct TextureNode *loadTextureNode(const char *filename, TextureNode **texture_list);

void cleanUp(struct GraphicsSettings *gs, struct Controller *input, struct TextureNode *textures);


//Vector functions.
float dotProductI(sf::Vector2i a, sf::Vector2i b);
float dotProductF(sf::Vector2f a, sf::Vector2f b);
float magnitudeI(sf::Vector2i a);
float magnitudeF(sf::Vector2f a);

#endif