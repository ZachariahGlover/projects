#ifndef __object_header
#define __object_header

#include <SFML/Graphics.hpp>

#include "utils.h"

class Object : public sf::Drawable {
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
			states.texture = texture_node->textures[current_animation];
			target.draw(sprite, states);
		}

	protected:
		sf::Vector2f size;
		sf::Vector2f center;
		sf::VertexArray sprite;
		TextureNode *texture_node;
		int current_animation;
		int current_frame;
		int current_orientation;
		int animated;
		float frame_time;

	public:
		Object();
		Object(sf::Vector2f s, sf::Vector2f p, TextureNode *tn, sf::Vector2f cfco);

		void setTextureNode(TextureNode *tn);
		void setSize(sf::Vector2f s);
		void setAnimation(int ca);
		void setOrientation(int o);

		void setPosition(sf::Vector2f p);

		sf::Vector2f *getCenterPointer();

		void animate(float dt);
		void updateTextureCoordinates();
};
#endif