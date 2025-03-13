/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_ENTITY_FACTORY
#define RRE_ENTITY_FACTORY

#include <string>

#include <tinyxml2.h>

#include "Entity.hpp"


namespace EntityFactory {

	/**
	 * Builds an entity from configuration.
	 *
	 * @param el
	 *   Parsed entity element.
	 */
	Entity build(tinyxml2::XMLElement* el);
}

#endif /* RRE_ENTITY_FACTORY */
