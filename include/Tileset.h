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
 * Image implementation representing a tileset.
 */
class Tileset : public ImageImpl {
private:
	/** Minimum global ID for this tileset in scene. */
	uint32_t first_gid;
	/** Maximum global ID for this tileset in scene. */
	uint32_t last_gid;

public:
	/**
	 * Tileset definition constructor.
	 *
	 * @param texture
	 *   Texture to draw with renderer.
	 * @param first_gid
	 *   Global ID start.
	 * @param tileHeight
	 *   Global ID end.
	 */
	Tileset(SDL_Texture* texture, uint16_t first_gid, uint16_t last_gid);

	/**
	 * Retrieves global ID start index.
	 *
	 * @return
	 *   Global ID start.
	 */
	uint32_t getFirstGID() { return this->first_gid; }

	/**
	 * Retrieves global ID end index.
	 *
	 * @return
	 *   Global ID end.
	 */
	uint32_t getLastGID() { return this->last_gid; }

	/**
	 * Checks if global ID represents this tileset.
	 *
	 * @param gid
	 *   Global ID to be checked.
	 * @return
	 *   `true` if global ID within range of this tileset's IDs.
	 */
	bool matches(uint32_t gid) {
		return gid >= this->first_gid && gid <= this->last_gid;
	}
};

#endif /* RRE_TILESET */
