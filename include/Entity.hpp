/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_ENTITY
#define RRE_ENTITY

#include <cstdint> // *int*_t
#include <string>

#include <SDL2/SDL_rect.h>

#include "Logger.hpp"
#include "MomentumDir.hpp"
#include "Object.hpp"
#include "Sprite.hpp"
#include "ViewportRenderer.hpp"


/**
 * Represents an entity object in scene.
 */
class Entity: public Object {
private:
	static Logger logger;

	/** Image drawn on viewport. */
	Sprite* sprite;

	/** Entity's collision rectangle. */
	SDL_Rect rect;

	/** Direction entity is moving. */
	uint8_t dir = MomentumDir::NONE;
	/** Last known horizontal direction. */
	uint8_t last_h_dir = MomentumDir::NONE;
	/** Last known vertical direction. */
	uint8_t last_v_dir = MomentumDir::NONE;
	/** Rate of momentum. */
	float momentum = 0;
	/** Default rate of momentum (0 means entity does not move). */
	float base_momentum = 0;

public:
	/**
	 * Creates an entity with collision rectangle.
	 *
	 * @param sprite
	 *   Entity's sprite to draw on viewport (`null` to draw nothing).
	 * @param width
	 *   Entity's pixel width.
	 * @param height
	 *   Entity's pixel height.
	 */
	Entity(Sprite* sprite, uint32_t width, uint32_t height);

	/**
	 * Creates an entity with collision rectangle using sprite's dimensions.
	 *
	 * @param sprite
	 *   Entity's sprite to draw on viewport (`null` to draw nothing).
	 */
	Entity(Sprite* sprite);

	/**
	 * Creates an entity with collision rectangle.
	 *
	 * @param sprite_id
	 *   String identifier to get sprite image from texture loader.
	 * @param width
	 *   Entity's pixel width.
	 * @param height
	 *   Entity's pixel height.
	 */
	Entity(std::string sprite_id, uint32_t width, uint32_t height);

	/**
	 * Creates an entity with collision rectangle using sprite's dimensions.
	 *
	 * @param sprite_id
	 *   String identifier to get sprite image from texture loader.
	 */
	Entity(std::string sprite_id);

	/**
	 * Copy constructor.
	 *
	 * @param other
	 *   Entity to be copied.
	 */
	Entity(const Entity& other): Object(other) {
		sprite = other.sprite;
		rect = other.rect;
		base_momentum = other.base_momentum;
	}

	/** Default constructor. */
	Entity(): Entity(nullptr) {}

	/** Default destructor. */
	~Entity() {
		// sprite instance is unique pointer so shouldn't need to destroy here
	}

	/** Overrides `Object.logic`. */
	void logic() override;

	/** Overrides `Object.equals`. */
	bool equals(const Object& obj) const override {
		if (!obj.instanceof<Entity>()) {
			return false;
		}
		const Entity* other = dynamic_cast<const Entity*>(&obj);
		return sprite == other->sprite && rect.x == other->rect.x && rect.y == other->rect.y
				&& rect.w == other->rect.w && rect.h == other->rect.h;
	}

	/**
	 * Update entity's position.
	 *
	 * @param x
	 *   New pixel position on horizontal axis.
	 */
	void setX(uint32_t x) { this->rect.x = x; }

	/**
	 * Update entity's position.
	 *
	 * @param y
	 *   New pixel position on vertical axis.
	 */
	void setY(uint32_t y) { this->rect.y = y; }

	/**
	 * Change the entity's collision dimensions.
	 *
	 * @param width
	 *   Entity's new pixel width.
	 */
	void setWidth(uint32_t width) { this->rect.w = width; }

	/**
	 * Change the entity's collision dimensions.
	 *
	 * @param width
	 *   Entity's new pixel width.
	 */
	void setheight(uint32_t height) { this->rect.h = height; }

	/**
	 * Retrieves entity's collision dimensions.
	 *
	 * @return
	 *   Collision rectangle.
	 */
	SDL_Rect getRect() { return this->rect; }

	/**
	 * Adds direction of momentum to entity.
	 *
	 * @param dir
	 *   Direction to be added.
	 * @return
	 *   Direction of momentum.
	 */
	uint8_t addDirection(uint8_t dir);

	/**
	 * Removes direction of momentum from entity.addDirection
	 *
	 * @param dir
	 *   Direction to be removed.
	 * @return
	 *   Direction of momentum.
	 */
	uint8_t removeDirection(uint8_t dir);

	/**
	 * Retrieves entity's direction.
	 *
	 * @return
	 *   Direction of momentum.
	 */
	uint8_t getDirection() { return dir; }

	/**
	 * Retrieves entity's horizontal direction.
	 *
	 * @return
	 *   Last known horizontal direction of momentum.
	 */
	uint8_t getHDirection() { return last_h_dir; }

	/**
	 * Retrieves entity's vertical direction.
	 *
	 * @return
	 *   Last known vertical direction of momentum.
	 */
	uint8_t getVDirection() { return last_v_dir; }

	/**
	 * Sets entity's rate of momentum per game logic step.
	 *
	 * @param momentum
	 *   New momentum.
	 */
	void setMomentum(float momentum) {
		this->momentum = momentum;
	}

	/**
	 * Retrieves entity's rate of momentum per game logic step.
	 *
	 * @return
	 *   Current momentum.
	 */
	float getMomentum() {
		return momentum;
	}

	/**
	 * Sets rate of momentum to use while entity is moving.
	 *
	 * @param momentum
	 *   Rate of momentum.
	 */
	void setBaseMomentum(float momentum) { base_momentum = momentum; }

	/**
	 * Checks if this entity collides on a horizontal or vertical line.
	 *
	 * @param x
	 *   Horizontal position of node.
	 * @param y
	 *   Vertial position of node.
	 * @param len
	 *   Pixel length of line.
	 * @param horizontal
	 *   Whether the line is oriented horizontally or vertically.
	 * @return
	 *   `true` if this entity's collision box clips vector at any point.
	 */
	bool collides(uint32_t x, uint32_t y, uint32_t len, bool horizontal);

	/**
	 * Checks if this entity collides with another.
	 *
	 * @param other
	 *   Other entity to collision against.
	 * @return
	 *   `true` if entities clip at any point.
	 */
	bool collides(Entity* other);

	/**
	 * Checks if the entity has a drawable sprite.
	 *
	 * @return
	 *   `true` if sprite is defined & marked ready.
	 */
	bool hasSprite() { return sprite != nullptr && sprite->ready(); }

	/**
	 * Draws entity sprite on viewport render.
	 *
	 * Overrides `Object.render`.
	 *
	 * @param viewport
	 *   Viewport renderer.
	 */
	void render(ViewportRenderer* viewport) override;
};


/** Null entity for checking state of initialization. */
static const Entity NullEntity;

#endif /* RRE_ENTITY */
