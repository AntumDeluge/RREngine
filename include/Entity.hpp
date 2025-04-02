/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_ENTITY
#define RRE_ENTITY

#include <cstdint> // *int*_t
#include <memory> // std::shared_ptr, std::make_shared

#include <SDL2/SDL_rect.h>

#include "Logger.hpp"
#include "Object.hpp"
#include "Renderer.hpp"
#include "Sprite.hpp"
#include "enum/FaceDir.hpp"
#include "enum/MomentumDir.hpp"


/**
 * Represents an entity object in scene.
 */
class Entity: public Object {
private:
	static Logger logger;

protected:
	/** Image drawn on viewport. */
	std::shared_ptr<Sprite> sprite;

	/** Entity's collision rectangle. */
	SDL_Rect rect;

	/** Direction entity is facing. */
	uint8_t face_dir = FaceDir::RIGHT;
	/** Direction entity is moving. */
	uint8_t dir = MomentumDir::NONE;
	/** Rate of momentum. */
	float momentum = 0;

	/**
	 * Entity's current energy level.
	 *
	 * FIXME: change to float?
	 */
	int32_t energy;

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
	Entity(std::shared_ptr<Sprite> sprite, uint32_t width, uint32_t height);

	/**
	 * Creates an entity with collision rectangle using sprite's dimensions.
	 *
	 * @param sprite
	 *   Entity's sprite to draw on viewport (`null` to draw nothing).
	 */
	Entity(std::shared_ptr<Sprite> sprite);

	/**
	 * Copy constructor.
	 *
	 * @param other
	 *   Entity to be copied.
	 */
	Entity(const Entity& other): Object(other) {
		sprite = other.sprite;
		rect = other.rect;
		energy = other.energy;
	}

	/** Default constructor. */
	Entity(): Entity(nullptr) {}

	/** Default destructor. */
	~Entity() {}

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
	void setHeight(uint32_t height) { this->rect.h = height; }

	/**
	 * Retrieves entity's collision dimensions.
	 *
	 * @return
	 *   Collision rectangle.
	 */
	SDL_Rect getRect() { return this->rect; }

	/**
	 * Adds direction of momentum to entity & updates facing direction.
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
	 * Retrieves gravitational force to apply to this entity.
	 *
	 * @return
	 *   Gravity force rate.
	 */
	float getGravity();

	/**
	 * Sets maximum energy value for this entity.
	 *
	 * TODO:
	 * - override in Player or Character class
	 * - set energy bar in Player or Character class (most entities won't have an energy bar to display)
	 *
	 * @param energy
	 *   Maximum energy.
	 */
	virtual void setBaseEnergy(int32_t energy);

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

	/** Action when entity hits left boundary of scene. */
	void onClipLeft();

	/** Action when entity hits right boundary of scene. */
	void onClipRight();

	/** Action when entity hits top boundary of scene. */
	void onClipTop();

	/** Action when entity hits bottom boundary of scene. */
	void onClipBottom();

	/**
	 * Checks if the entity has a drawable sprite.
	 *
	 * @return
	 *   `true` if sprite is defined & marked ready.
	 */
	bool hasSprite() { return sprite != nullptr && sprite->ready(); }

	/** Overrides `Object::render`. */
	virtual void render(Renderer* ctx) override;
};


/** Null entity for checking state of initialization. */
static const Entity NullEntity;

#endif /* RRE_ENTITY */
