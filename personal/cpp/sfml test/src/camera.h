#ifndef __camera_header
#define __camera_header

#include <SFML/Graphics.hpp>

//The camera class.
//Stores a bunch of fairly self explanatory settings.
//Provides a set of functions to modify/retrieve some settings.
//Also provides some functions to perform some unique data modifications.
class Camera {
	protected:
		sf::View view;
		sf::Vector2f *focus;
		sf::Vector2f move;

	public:
		Camera();
		Camera(int ww, int wh, int cx, int cy, sf::Vector2f *f);
		Camera(sf::Vector2f sv, sf::Vector2f cv, sf::Vector2f *f);

		void setSize(int width, int height);
		void setCenter(int cx, int cy);

		void setSize(sf::Vector2f sv);
		void setCenter(sf::Vector2f cv);

		void setFocus(sf::Vector2f *fv);

		sf::View getView();

		void panToFocus(float pan);
};
#endif