/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_PLAYER
#define RRE_PLAYER

#include <cstdint> // *int*_t

#include "Entity.hpp"
#include "Logger.hpp"


class Player: public Entity {
private:
	static Logger logger;

	/** Last horizontal position detected. */
	uint32_t x_prev;
	/** Last vertical position detected. */
	uint32_t y_prev;

public:
	/**
	 * Copy constructor.
	 *
	 * @param other
	 *   Player to be copied.
	 */
	Player(const Player& other): Entity(other) {}

	/** Overrides `Entity::logic`. */
	void logic() override;

	/** Overrides `Object::onAdded`. */
	void onAdded(SceneImpl* scene) override;

private:
	void onMoved();
};

#endif /* RRE_PLAYER */
