/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_ENTITY_STORE
#define RRE_ENTITY_STORE

#include <string>

#include "Character.hpp"
#include "Entity.hpp"
#include "Player.hpp"


/**
 * Caches entities loaded from configuration.
 */
namespace EntityStore {

	/**
	 * Caches all configured entities into memory.
	 *
	 * @return
	 *   `true` if loading succeeded without error.
	 */
	bool load();

	/**
	 * Retrieves an entity from cache.
	 *
	 * FIXME:
	 * - return `shared_ptr`
	 *
	 * @param id
	 *   Entity identifier.
	 * @return
	 *   Copy of an entity instance. If not found, `NullEntity` is returned.
	 */
	Entity get(std::string id);

	/**
	 * Retrieves a character from cache.
	 *
	 * FIXME:
	 * - return `shared_ptr`
	 *
	 * @param id
	 *   Character identifier.
	 * @return
	 *   Copy of an character instance. If not found, `NullEntity` is returned.
	 */
	Character getCharacter(std::string id);

	/**
	 * Retrieves a player from cache.
	 *
	 * FIXME:
	 * - return `shared_ptr`
	 * - should `Player` instances by `unique_ptr`?
	 *
	 * @param id
	 *   Player identifier.
	 * @return
	 *   Copy of an player instance. If not found, `NullEntity` is returned.
	 */
	Player getPlayer(std::string id);
}

#endif /* RRE_ENTITY_STORE */
