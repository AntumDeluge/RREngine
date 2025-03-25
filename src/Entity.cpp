/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <SDL2/SDL_render.h>

#include "Entity.hpp"
#include "store/SpriteStore.hpp"

#if RRE_DEBUGGING
#include "SingletonRepo.hpp"
#endif

using namespace std;


Logger Entity::logger = Logger::getLogger("Entity");

Entity::Entity(Sprite* sprite, uint32_t width, uint32_t height) {
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

Entity::Entity(std::string sprite_id, uint32_t width, uint32_t height):
		Entity(SpriteStore::get(sprite_id), width, height) {}

Entity::Entity(string sprite_id): Entity(SpriteStore::get(sprite_id)) {}


void Entity::logic() {
	if (scene && !scene->collidesGround(rect)) {
		if (sprite->getModeId() != "fall") {
			sprite->setMode("fall");
		}
		// apply gravity
		rect.y += getGravity() * 2;
	} else if (sprite->getModeId() == "fall") {
		if (dir & MomentumDir::LEFT || dir & MomentumDir::RIGHT) {
			sprite->setMode("run");
		} else {
			sprite->setMode("idle");
		}
	}

	if (momentum > 0 && !scene->collidesWall(dir, rect)) {
		if (dir & MomentumDir::RIGHT) {
			this->rect.x += momentum;
		} else if (dir & MomentumDir::LEFT) {
			this->rect.x -= momentum;
		}
	}
}

uint8_t Entity::addDirection(uint8_t dir) {
	if (dir == MomentumDir::LEFT || dir == MomentumDir::RIGHT) {
		if (dir == MomentumDir::LEFT) {
			// remove old direction in case button/key not released
			this->dir &= ~MomentumDir::RIGHT;
			// update facing direction
			face_dir = FaceDir::LEFT;
		} else {
			// remove old direction in case button/key not released
			this->dir &= ~MomentumDir::LEFT;
			// update facing direction
			face_dir = FaceDir::RIGHT;
		}
		momentum = getFloat("base_momentum");
		if (sprite->getModeId() != "fall") {
			// update animation if not falling
			this->sprite->setMode("run");
		}
	} else if (dir == MomentumDir::UP || dir == MomentumDir::DOWN) {
		momentum = getFloat("base_momentum");
	}
	this->dir |= dir;
	return this->dir;
}

uint8_t Entity::removeDirection(uint8_t dir) {
	this->dir &= ~dir;
	if (this->dir == MomentumDir::NONE) {
		momentum = 0;
		if (sprite->getModeId() != "fall") {
			// update animation if not falling
			this->sprite->setMode("idle");
		}
	}
	return this->dir;
}

float Entity::getGravity() {
	if (scene) {
		return scene->getGravity(rect.x + rect.w / 2, rect.y + rect.h);
	}
	if (has("base_gravity")) {
		return getFloat("base_gravity");
	}
	return 1.0;
}

bool Entity::collides(uint32_t x, uint32_t y, uint32_t len, bool horizontal) {
	// this entity's right-most & bottom-most pixel collision
	uint32_t right = this->rect.x + this->rect.w;
	uint32_t bottom = this->rect.y + this->rect.h;

	if (horizontal) {
		uint32_t x_max = x + len;
		if ((bottom >= y && this->rect.y <= y) && (right >= x && this->rect.x <= x_max)) {
			return true;
		}
	} else {
		uint32_t y_max = y + len;
		if ((right >= x && this->rect.x <= x) && (bottom >= y && this->rect.y <= y_max)) {
			return true;
		}
	}
	return false;
}

bool Entity::collides(Entity* other) {
	SDL_Rect o_rect = other->getRect();
	// other entity's right-most & bottom-most pixel collision
	uint32_t o_right = o_rect.x + o_rect.w;
	//uint32_t o_top = o_rect.y;
	uint32_t o_bottom = o_rect.y + o_rect.h;

	// this entity's right-most & bottom-most pixel collision
	uint32_t t_right = this->rect.x + this->rect.w;
	uint32_t t_bottom = this->rect.y + this->rect.h;

	// check for clipping at any point
	return ((this->rect.x >= o_rect.x && this->rect.x <= o_right)
			|| (t_right >= o_rect.x && t_right <= o_right))
		&& ((this->rect.y >= o_rect.y && this->rect.y <= o_bottom)
			|| (t_bottom >= o_rect.y && t_bottom <= o_bottom));
}

void Entity::render(ViewportImpl* viewport) {
	if (!hasSprite()) {
		return;
	}

	SDL_RendererFlip flags = SDL_FLIP_NONE;
	if (face_dir == FaceDir::LEFT) {
		flags = SDL_FLIP_HORIZONTAL;
	}

	// horizontally center sprite drawing
	int32_t offset_x = (sprite->getTileWidth() - rect.w) / 2;
	// align sprite to bottom of entity
	int32_t offset_y = sprite->getTileHeight() - rect.h;

	sprite->render(viewport, rect.x - offset_x, rect.y - offset_y, flags);

#if RRE_DEBUGGING
	// debug collision box & sprite alignment
	Renderer* renderer = GetRenderer();
	renderer->save();
	renderer->setDrawColor(0, 255, 0, 255);
	renderer->drawRect(rect);
	renderer->restore();
#endif
}
