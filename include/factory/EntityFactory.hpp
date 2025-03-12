/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_ENTITY_FACTORY
#define RRE_ENTITY_FACTORY

#include <string>

#include "Entity.h"


namespace EntityFactory {

	/**
	 * Creates a new entity from configuration.
	 *
	 * TODO: create from an entity template stored in memory instead of reading from filesystem
	 *       every call
	 *
	 * @param id
	 *   Entity's identifier.
	 */
	Entity getEntity(std::string id);
}

#endif /* RRE_ENTITY_FACTORY */
