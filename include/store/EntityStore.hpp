/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_ENTITY_STORE
#define RRE_ENTITY_STORE

#include <string>

#include "Entity.h"


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
	 * @param id
	 *   Entity identifier.
	 * @return
	 *   Copy of entity instance. If not found, `NullEntity` is returned.
	 */
	Entity getEntity(std::string id);
}

#endif /* RRE_ENTITY_STORE */
