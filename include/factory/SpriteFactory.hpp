/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SPRITE_FACTORY
#define RRE_SPRITE_FACTORY

#include <memory>

#include <pugixml.hpp>

#include "Sprite.hpp"


/**
 * Builds sprites from configuration.
 */
namespace SpriteFactory {

	/**
	 * Builds a unique sprite instance from configuration.
	 *
	 * @param el
	 *   Parsed "sprite" element.
	 * @return
	 *   Unique sprite instance.
	 */
	std::shared_ptr<Sprite> build(pugi::xml_node el);
}

#endif /* RRE_SPRITE_FACTORY */
