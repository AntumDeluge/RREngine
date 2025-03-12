/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SPRITE_STORE
#define RRE_SPRITE_STORE

#include <string>

#include "Sprite.h"


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
	 * @param id
	 *   Sprite identifier.
	 * @return
	 *   Copy of sprite instance. If not found, an uninitialized sprite is returned. Can be checked
	 *   with `Sprite.ready()`.
	 */
	Sprite getSprite(std::string id);
}

#endif /* RRE_SPRITE_STORE */
