/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "Tileset.h"


Tileset::Tileset(SDL_Texture* texture, uint16_t tileWidth, uint16_t tileHeight)
		: ImageImpl(texture) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
}
