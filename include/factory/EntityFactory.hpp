/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_ENTITY_FACTORY
#define RRE_ENTITY_FACTORY

#include <string>

#include <pugixml.hpp>

#include "template/EntityTemplate.hpp"


namespace EntityFactory {

	/**
	 * Builds a unique entity instance from configuration.
	 *
	 * @param el
	 *   Parsed entity element.
	 * @return
	 *   Entity template.
	 */
	EntityTemplate build(pugi::xml_node el);
}

#endif /* RRE_ENTITY_FACTORY */
