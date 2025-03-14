/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "Entity.hpp"
#include "Path.hpp"
#include "TextureLoader.hpp"

using namespace std;


Logger Entity::logger = Logger::getLogger("Entity");

Entity::Entity(Sprite* sprite, uint16_t width, uint16_t height) {
	this->sprite = sprite;
	// NOTE: are values of `SDL_Rect` implicitly set to 0 by default?
	this->rect.x = 0;
	this->rect.y = 0;
	this->rect.w = width;
	this->rect.h = height;
}

Entity::Entity(Sprite* sprite) {
	this->sprite = sprite;
	this->rect.x = 0;
	this->rect.y = 0;
	if (this->sprite != nullptr) {
		// default to sprite dimensions
		this->rect.w = this->sprite->getWidth();
		this->rect.h = this->sprite->getHeight();
	} else {
		this->rect.w = 0;
		this->rect.h = 0;
	}
}

Entity::Entity(std::string sprite_id, uint16_t width, uint16_t height):
		Entity(new Sprite(TextureLoader::load(Path::join("sprite", sprite_id))), width, height) {}

Entity::Entity(string sprite_id):
Entity(new Sprite(TextureLoader::load(Path::join("sprite", sprite_id)))) {}


bool Entity::collides(uint16_t x, uint16_t y, uint16_t len, bool horizontal) {
	// this entity's right-most & bottom-most pixel collision
	uint16_t right = this->rect.x + this->rect.w;
	uint16_t bottom = this->rect.y + this->rect.h;

	if (horizontal) {
		uint16_t x_max = x + len;
		if ((bottom >= y && this->rect.y <= y) && (right >= x && this->rect.x <= x_max)) {
			return true;
		}
	} else {
		uint16_t y_max = y + len;
		if ((right >= x && this->rect.x <= x) && (bottom >= y && this->rect.y <= y_max)) {
			return true;
		}
	}
	return false;
}

bool Entity::collides(Entity* other) {
	SDL_Rect o_rect = other->getRect();
	// other entity's right-most & bottom-most pixel collision
	uint16_t o_right = o_rect.x + o_rect.w;
	//uint16_t o_top = o_rect.y;
	uint16_t o_bottom = o_rect.y + o_rect.h;

	// this entity's right-most & bottom-most pixel collision
	uint16_t t_right = this->rect.x + this->rect.w;
	uint16_t t_bottom = this->rect.y + this->rect.h;

	// check for clipping at any point
	return ((this->rect.x >= o_rect.x && this->rect.x <= o_right)
			|| (t_right >= o_rect.x && t_right <= o_right))
		&& ((this->rect.y >= o_rect.y && this->rect.y <= o_bottom)
			|| (t_bottom >= o_rect.y && t_bottom <= o_bottom));
}

void Entity::render(ViewportRenderer* viewport) {
	if (this->sprite != nullptr) {
		this->sprite->render(viewport, this->rect.x, this->rect.y);
	}
}
