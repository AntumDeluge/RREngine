/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_PLAYER
#define RRE_PLAYER

#include <cstdint> // *int*_t
#include <memory> // std::shared_ptr, std::make_shared

#include "Character.hpp"
#include "Logger.hpp"
#include "Sprite.hpp"


/**
 * A playable character.
 */
class Player: public Character {
private:
	static Logger logger;

	/** Last horizontal position detected. */
	uint32_t x_prev;
	/** Last vertical position detected. */
	uint32_t y_prev;

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
	Player(std::shared_ptr<Sprite> sprite, uint32_t width, uint32_t height);

	/**
	 * Creates an entity with collision rectangle using sprite's dimensions.
	 *
	 * @param sprite
	 *   Entity's sprite to draw on viewport (`null` to draw nothing).
	 */
	Player(std::shared_ptr<Sprite> sprite);


	/**
	 * Copy constructor.
	 *
	 * @param other
	 *   Player to be copied.
	 */
	Player(const Player& other);

	/** Overrides `Entity::logic`. */
	void logic() override;

	/** Overrides `Object::onAdded`. */
	void onAdded(SceneImpl* scene) override;

private:
	void onMoved();
};

#endif /* RRE_PLAYER */
