/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SCENE
#define RRE_SCENE

#include <cstdint> // uint*_t
#include <string>
#include <vector>

#include "ImageImpl.h"
#include "Tileset.h"


/**
 * Class to represent a scene being drawn on the viewport.
 *
 * TODO:
 * - need collision mapping to match terrain layer
 * - support additional background with parallax scrolling
 */
class Scene {
private:
	/** Pixel width of each tile. */
	uint16_t tile_width;
	/** Pixel height of each tile. */
	uint16_t tile_height;

	/** Scene tilesets. */
	std::vector<Tileset> tilesets;

	/** Rendered background image. */
	ImageImpl background;
	/** Rendered terrain/collision image. */
	ImageImpl terrain;
	/** Rendered foreground image. */
	ImageImpl foreground;

public:
	Scene(uint16_t tile_width, uint16_t tile_height) {
		this->tile_width = tile_width;
		this->tile_height = tile_height;
	}

	void addTileset(Tileset tileset) {
		this->tilesets.push_back(tileset);
	}

	/**
	 * Builds scene background layer.
	 *
	 * FIXME: might need to use different type for `data` parameter
	 *
	 * @param data
	 *   Data defining tile drawing order.
	 */
	void renderBackground(std::string data);

	/**
	 * Builds scene terrain layer.
	 *
	 * FIXME: might need to use different type for `data` parameter
	 *
	 * @param data
	 *   Data defining tile drawing order.
	 */
	void renderTerrain(std::string data);

	/**
	 * Builds scene foreground layer.
	 *
	 * FIXME: might need to use different type for `data` parameter
	 *
	 * @param data
	 *   Data defining tile drawing order.
	 */
	void renderForeground(std::string data);
};

#endif /* RRE_SCENE */
