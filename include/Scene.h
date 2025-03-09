/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SCENE
#define RRE_SCENE

#include <cstdint> // uint*_t
#include <vector>

#include <tmxlite/ImageLayer.hpp>
#include <tmxlite/TileLayer.hpp>

#include "Tileset.h"


/**
 * Class to represent a scene being drawn on the viewport.
 *
 * TODO:
 * - need collision mapping to match collision layer
 * - support additional background with parallax scrolling
 * - create separate class called SceneBuilder to serve as framework to rendering scene
 */
class Scene {
private:
	/** Pixel width of each tile. */
	uint16_t tile_width;
	/** Pixel height of each tile. */
	uint16_t tile_height;

	/** Scene tilesets. */
	std::vector<Tileset> tilesets;

	/** Parallax scrolling background layer 1. */
	tmx::ImageLayer* s_background;
	/** Parallax scrolling background layer 2. */
	tmx::ImageLayer* s_background2;

	/** Bottom tiled layer. */
	tmx::TileLayer* background;
	/** Terrain layer drawn under entities. */
	tmx::TileLayer* terrain;
	/** Entities located in scene. */
	tmx::TileLayer* entities;
	/** Terrain layer containing collision info. */
	tmx::TileLayer* collision;
	/** Top tiled layer drawn over entities. */
	tmx::TileLayer* foreground;

	tmx::ImageLayer* s_foreground;

public:
	Scene(uint16_t tile_width, uint16_t tile_height) {
		this->tile_width = tile_width;
		this->tile_height = tile_height;

		this->s_background = nullptr;
		this->s_background2 = nullptr;
		this->background = nullptr;
		this->terrain = nullptr;
		this->entities = nullptr;
		this->collision = nullptr;
		this->foreground = nullptr;
		this->s_foreground = nullptr;
	}

	~Scene() {
		delete this->s_background;
		this->s_background = nullptr;
		delete this->s_background2;
		this->s_background2 = nullptr;
		delete this->background;
		this->background = nullptr;
		delete this->terrain;
		this->terrain = nullptr;
		delete this->entities;
		this->entities = nullptr;
		delete this->collision;
		this->collision = nullptr;
		delete this->foreground;
		this->foreground = nullptr;
		delete this->s_foreground;
		this->s_foreground = nullptr;
	}

	void addTileset(Tileset tileset) {
		this->tilesets.push_back(tileset);
	}

	/**
	 * Builds scene layers.
	 */
	void render();
};

#endif /* RRE_SCENE */
