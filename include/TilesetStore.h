/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_TILESET_STORE
#define RRE_TILESET_STORE

#include <string>

#include "Tileset.h"


/**
 * Functions for loading & retrieving tileset image data.
 */
namespace TilesetStore {

	bool load();

	/**
	 * Retrieves from memory or builds a tileset.
	 *
	 * FIXME: deprecated, no longer used
	 *
	 * @param rpath
	 *   File path relative to tileset directory (excluding *.png suffix).
	 */
	Tileset* getTileset(std::string rpath);
};

#endif /* RRE_TILESET_STORE */
