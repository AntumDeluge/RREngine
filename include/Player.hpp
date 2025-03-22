/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_PLAYER
#define RRE_PLAYER

#include "Entity.hpp"
#include "Logger.hpp"


class Player: public Entity {
private:
	static Logger logger;

public:
	/**
	 * Copy constructor.
	 *
	 * @param other
	 *   Player to be copied.
	 */
	Player(const Player& other): Entity(other) {}
};

#endif /* RRE_PLAYER */
