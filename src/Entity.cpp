/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <algorithm> // min, max

#include <SDL2/SDL_render.h>

#include "Entity.hpp"
#include "store/SpriteStore.hpp"

using namespace std;


Logger Entity::logger = Logger::getLogger("Entity");

Entity::Entity(shared_ptr<Sprite> sprite, uint32_t width, uint32_t height) {
	this->sprite = sprite;
	// NOTE: are values of `SDL_Rect` implicitly set to 0 by default?
	this->rect.x = 0;
	this->rect.y = 0;
	this->rect.w = width;
	this->rect.h = height;
	onDepletedInternal = nullptr;
	// default energy
	energy = 1.0;
	set("base_energy", energy);
}

Entity::Entity(shared_ptr<Sprite> sprite) {
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
	onDepletedInternal = nullptr;
	// default value for energy & base energy
	energy = 1.0;
	set("base_energy", energy);
}


void Entity::logic() {
	if (gravity > 0 && scene && !scene->collidesGround(rect)) {
		if (sprite->getModeId() != "fall") {
			sprite->setMode("fall");
		}
		// apply gravity
		rect.y += getGravity() * (4 * gravity);
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

	if (rect.x < 0) {
		rect.x = 0;
		onClipLeft();
	} else if (rect.x + rect.w > scene->getWidth()) {
		rect.x = scene->getWidth() - rect.w;
		onClipRight();
	}
	if (rect.y < 0) {
		rect.y = 0;
		onClipTop();
	} else if (rect.y + rect.h > scene->getHeight()) {
		rect.y = scene->getHeight() - rect.h;
		onClipBottom();
	}
}

void Entity::onAdded(SceneImpl* scene) {
	Object::onAdded(scene);
	gravity = getFloat("gravity", 1.0f);
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

void Entity::setBaseEnergy(int32_t energy) {
	set("base_energy", energy);
}

void Entity::recoverEnergy(float amount) {
	// "base_energy" should unsigned int, but retrieve float for correct comparison
	energy = min(energy + amount, getFloat("base_energy"));
}

void Entity::depleteEnergy(float amount) {
	energy = amount > energy ? 0 : energy - amount;
	if (energy == 0) {
		onDepleted();
	}
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

void Entity::onClipLeft() {
	// DEBUG:
	logger.debug("Entity hit left boundary of scene");

	// TODO:
}

void Entity::onClipRight() {
	// DEBUG:
	logger.debug("Entity hit right boundary of scene");

	// TODO:
}

void Entity::onClipTop() {
	// DEBUG:
	logger.debug("Entity hit top boundary of scene");

	// TODO:
}

void Entity::onClipBottom() {
	// DEBUG:
	logger.debug("Entity hit bottom boundary of scene");

	// TODO:
}

void Entity::render(Renderer* ctx) {
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

	SDL_Rect draw_rect = rect;
	draw_rect.x -= scene->getOffsetX();
	draw_rect.y -= scene->getOffsetY() + offset_y;

	sprite->render(ctx, draw_rect.x - offset_x, draw_rect.y - offset_y, flags);

#if RRE_DEBUGGING
	// debug collision box & sprite alignment
	ctx->save();
	ctx->setDrawColor(0, 255, 0, 255);
	ctx->drawRect(draw_rect);
	ctx->restore();
#endif
}
