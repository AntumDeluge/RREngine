/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "Tileset.hpp"


Tileset::Tileset(SDL_Texture* texture, uint16_t first_gid, uint16_t last_gid): Image(texture) {
	this->first_gid = first_gid;
	this->last_gid = last_gid;
}
