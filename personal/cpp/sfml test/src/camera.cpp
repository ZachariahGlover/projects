#include <SFML/Graphics.hpp>

#include "camera.h"

//Default constructor.
Camera::Camera() {
	focus = NULL;
	move = sf::Vector2f(0, 0);
	view = sf::View(sf::Vector2f(512, 288), sf::Vector2f(1024, 576));
};

//Contructor using ints for most settings.
Camera::Camera(int ww, int wh, int cx, int cy, sf::Vector2f *f) {
	focus = f;
	move = sf::Vector2f(0, 0);
	view = sf::View(sf::Vector2f(cx, cy), sf::Vector2f(ww, wh));
};

//Contructor using vectors for most settings.
Camera::Camera(sf::Vector2f sv, sf::Vector2f cv, sf::Vector2f *f) {
	focus = f;
	move = sf::Vector2f(0, 0);
	view = sf::View(cv, sv);
};

//Camera sets with ints.
void Camera::setSize(int width, int height) {
	view.setSize(sf::Vector2f(width, height));
}
void Camera::setCenter(int cx, int cy) {
	view.setCenter(sf::Vector2f(cx, cy));
}

//Camera sets with vectors.
void Camera::setSize(sf::Vector2f sv) { 
	view.setSize(sv);
}
void Camera::setCenter(sf::Vector2f cv) {
	view.setCenter(cv);
}

//Set function for focus using a vector pointer.
void Camera::setFocus(sf::Vector2f *fv) { 
	focus = fv;
}

//Return's the camera's view parameters.
sf::View Camera::getView() {
	return view;
}

/*
 * panToFocus(float) -> void
 * Moves the camera's view towards its focus point.
 * Moves at a rate determined by pan.
 * 0.0 takes infinitely long, 1.0 is instantaneous.
 * 0.0 < pan <= 1.0
 */
void Camera::panToFocus(float pan) {

	//Calculate how much to move the view.
	move = *focus - view.getCenter();
	move = move * pan;
	move = move + view.getCenter();

	//Move the view.
	setCenter(move);
}