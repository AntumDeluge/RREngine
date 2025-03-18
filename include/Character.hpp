/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_CHARACTER
#define RRE_CHARACTER

#include <cstdint> // *int*_t
#include <string>

#include "Callable.hpp"
#include "Entity.hpp"
#include "Logger.hpp"
#include "Sprite.hpp"


/**
 * An NPC or playable character.
 */
class Character: public Entity {
private:
	static Logger logger;

	/** Default energy level. */
	uint32_t max_energy = 28;
	uint32_t energy = 28;

	Callable* onDepletedInternal = nullptr;

public:
	Character(Sprite* sprite, uint32_t width, uint32_t height);
	Character(Sprite* sprite);
	Character(std::string sprite_id, uint32_t width, uint32_t height);
	Character(std::string sprite_id);

	void recoverEnergy(uint32_t amount);

	void depleteEnergy(uint32_t amount);

	void onDepleted() {
		if (onDepletedInternal != nullptr) {
			onDepletedInternal->call();
		}
	}

	void setOnDepleted(Callable* onDepleted) {
		onDepletedInternal = onDepleted;
	}
};

#endif /* RRE_CHARACTER */
