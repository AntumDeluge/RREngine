/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_TILESET
#define RRE_TILESET

#include <cstdint>

#include "ImageImpl.h"


/**
 * Image implemtation representing a tileset.
 */
class Tileset : public ImageImpl {
private:
	/** Single tile width. */
	uint16_t tileWidth;
	/** Single tile height. */
	uint16_t tileHeight;

public:
	/**
	 * Tileset definition constructor.
	 *
	 * @param texture
	 *   Texture to draw with renderer.
	 * @param tileWidth
	 *   Single tile width in pixels.
	 * @param tileHeight
	 *   Single tile height in pixels.
	 */
	Tileset(SDL_Texture* texture, uint16_t tileWidth, uint16_t tileHeight);

	/**
	 * Retrieves tile width.
	 *
	 * @return
	 *   Defined width of a single tile for this tileset.
	 */
	uint16_t getTileWidth() { return this->tileWidth; }

	/**
	 * Retrieves tile height.
	 *
	 * @return
	 *   Defined height of a single tile for this tileset.
	 */
	uint16_t getTileHeight() { return this->tileHeight; }
};

#endif /* RRE_TILESET */
