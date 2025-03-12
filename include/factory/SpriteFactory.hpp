/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SPRITE_FACTORY
#define RRE_SPRITE_FACTORY

#include <tinyxml2.h>

#include "Sprite.h"


/**
 * Builds sprites from configuration.
 */
namespace SpriteFactory {

	/**
	 * Builds a sprite from configuration.
	 *
	 * @param el
	 *   Parsed "sprite" element.
	 */
	Sprite build(tinyxml2::XMLElement* el);
}

#endif /* RRE_SPRITE_FACTORY */
