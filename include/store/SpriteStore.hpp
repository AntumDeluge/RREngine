/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SPRITE_STORE
#define RRE_SPRITE_STORE

#include <string>

#include "Sprite.hpp"


/**
 * Caches sprites loaded from configuration.
 */
namespace SpriteStore {

	/**
	 * Caches all configured sprites into memory.
	 *
	 * @return
	 *   `true` if loading succeeded without error.
	 */
	bool load();

	/**
	 * Retrieves a sprite from cache.
	 *
	 * NOTE: perhaps should return a shared pointer
	 *
	 * @param id
	 *   Sprite identifier.
	 * @return
	 *   Reference to a sprite instance. If not found, an uninitialized sprite is returned. Can be
	 *   checked with `Sprite.ready()`.
	 */
	Sprite* get(std::string id);
}

#endif /* RRE_SPRITE_STORE */
