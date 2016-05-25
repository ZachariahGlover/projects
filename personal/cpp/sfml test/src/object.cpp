#include <math.h>

#include <SFML/Graphics.hpp>

#include "object.h"
#include "utils.h"

//Default constructor.
Object::Object() {
	sprite = sf::VertexArray(sf::Quads, 4);
	size = sf::Vector2f(0, 0);
	setPosition(sf::Vector2f(0, 0));
	texture_node = NULL;
	current_animation = 0;
	current_frame = 0;
	current_orientation = 0;
	animated = 0;
	frame_time = 0.0f;
}

//Constructor with parameters.
Object::Object(sf::Vector2f s, sf::Vector2f p, TextureNode *tn, sf::Vector2f cfco) {
	sprite = sf::VertexArray(sf::Quads, 4);
	size = s;
	setPosition(p);
	texture_node = tn;
	current_animation = 0;
	current_frame = 0;
	current_orientation = 0;
	animated = 1;
	frame_time = 0.0f;
}

//Basic variable set functions.
void Object::setTextureNode(TextureNode *tn) {
	texture_node = tn;
}
void Object::setSize(sf::Vector2f s) {
	size = s;
}
void Object::setAnimation(int ca) {
	current_animation = ca;
	updateTextureCoordinates();
}
void Object::setOrientation(int o) {
	current_orientation = o;
	updateTextureCoordinates();
}

//Set functions that require some work.
void Object::setPosition(sf::Vector2f p) {

	//Find/set our new center.
	center = sf::Vector2f(p.x + (size.x / 2), p.y + (size.y / 2));

	//Set the position.
	sprite[0].position = sf::Vector2f(p.x, p.y);
	sprite[1].position = sf::Vector2f(p.x + size.x, p.y);
	sprite[2].position = sf::Vector2f(p.x + size.x, p.y + size.y);
	sprite[3].position = sf::Vector2f(p.x, p.y + size.y);
}

//Get for a pointer to the center vector.
sf::Vector2f *Object::getCenterPointer() {
	return &center;
}

/*
 * animate(float) -> void
 * This function animates the sprite based on its current animation.
 * Takes in dt - the time since the last animation call was made.
 * Once the time since the last frame was rendered is appropriate,
 * we switch to the next frame.
 * Currently animates at about 60fps.
 */
void Object::animate(float dt) {
	if (animated) {

		//Increase frame time by dt.
		frame_time += dt;

		//Check if we should advance the animation frame.
		if (!(frame_time < 0.0167f)) {

			//Determine how many frames we should advance and set the current frame.
			int next_frame = (current_frame + round(frame_time / 0.0167f));
			current_frame = next_frame % texture_node->num_frames[current_animation];

			updateTextureCoordinates();

			//Reset frame time.
			frame_time = 0.0f;
		}
	}
}

/*
 * updateTextureCoordinates() -> void
 * Updates the texture coordinates to work with the current
 * animation and orientation.
 */
void Object::updateTextureCoordinates() {

	//Find the points to move the texture coordinates to.
	float sx = current_frame * texture_node->frame_sizes[current_animation].x;
	float sy = current_orientation * texture_node->frame_sizes[current_animation].y;
	float ex = sx + texture_node->frame_sizes[current_animation].x;
	float ey = sy + texture_node->frame_sizes[current_animation].y;

	//Move the texture coordinates.
	sprite[0].texCoords = sf::Vector2f(sx, sy);
	sprite[1].texCoords = sf::Vector2f(ex, sy);
	sprite[2].texCoords = sf::Vector2f(ex, ey);
	sprite[3].texCoords = sf::Vector2f(sx, ey);
}
