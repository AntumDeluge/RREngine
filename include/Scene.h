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

#include "Entity.h"
#include "Tileset.h"
#include "ViewportRenderer.h"


/**
 * Class to represent a scene being drawn on the viewport.
 *
 * TODO:
 * - need collision mapping to match collision layer
 * - support additional background with parallax scrolling
 * - create separate class called SceneBuilder to serve as framework to rendering scene
 * - rename file to Scene.hpp
 * - don't use pointers for layers
 * - defined a SceneLayer class that can support animation
 */
class Scene {
private:
	/** Individual tile pixel width. */
	uint16_t tile_width;
	/** Individual tile pixel height. */
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
	tmx::TileLayer* objects;
	/** Terrain layer containing collision info. */
	tmx::TileLayer* collision;
	/** Top tiled layer drawn over entities. */
	tmx::TileLayer* foreground;

	/** Parallax scrolling foreground layer. */
	tmx::ImageLayer* s_foreground;

	/** Entities currently occupying this scene. */
	std::vector<Entity*> entities;

public:
	/**
	 * Creates a new scene.
	 *
	 * @param tile_width
	 *   Individual tile pixel width.
	 * @param tile_height
	 *   Individual tile pixel height.
	 */
	Scene(uint16_t tile_width, uint16_t tile_height) {
		this->tile_width = tile_width;
		this->tile_height = tile_height;

		this->s_background = nullptr;
		this->s_background2 = nullptr;
		this->background = nullptr;
		this->terrain = nullptr;
		this->objects = nullptr;
		this->collision = nullptr;
		this->foreground = nullptr;
		this->s_foreground = nullptr;
	}

	/** Default destructor. */
	~Scene() {
		delete this->s_background;
		this->s_background = nullptr;
		delete this->s_background2;
		this->s_background2 = nullptr;
		delete this->background;
		this->background = nullptr;
		delete this->terrain;
		this->terrain = nullptr;
		delete this->objects;
		this->objects = nullptr;
		delete this->collision;
		this->collision = nullptr;
		delete this->foreground;
		this->foreground = nullptr;
		delete this->s_foreground;
		this->s_foreground = nullptr;

		for (Entity* e: this->entities) {
			delete e;
			e = nullptr;
		}
		this->entities.clear();
	}

	/**
	 * Adds a tileset to use in scene.
	 *
	 * @param tileset
	 *   Tileset to be added.
	 */
	void addTileset(Tileset tileset) {
		this->tilesets.push_back(tileset);
	}

	/**
	 * Draws scene on renderer.
	 *
	 * @param viewport
	 *   Viewport renderer.
	 */
	void render(ViewportRenderer* viewport);

	/**
	 * Sets layer to use for scrolling background 1.
	 *
	 * @param layer
	 *   Image layer definition.
	 */
	void setLayerSBackground(tmx::ImageLayer* layer) { this->s_background = layer; }

	/**
	 * Sets layer to use for scrolling background 2.
	 *
	 * @param layer
	 *   Image layer definition.
	 */
	void setLayerSBackground2(tmx::ImageLayer* layer) { this->s_background2 = layer; }

	/**
	 * Sets layer to use for background.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerBackground(tmx::TileLayer* layer) { this->background = layer; }

	/**
	 * Sets layer to use for terrain.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerTerrain(tmx::TileLayer* layer) { this->terrain = layer; }

	/**
	 * Sets layer to use for objects.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerObjects(tmx::TileLayer* layer) { this->objects = layer; }

	/**
	 * Sets layer to use for collision.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerCollision(tmx::TileLayer* layer) { this->collision = layer; }

	/**
	 * Sets layer to use for foreground.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerForeground(tmx::TileLayer* layer) { this->foreground = layer; }

	/**
	 * Sets layer to use for scrolling foreground.
	 *
	 * @param layer
	 *   Image layer definition.
	 */
	void setLayerSForeground(tmx::ImageLayer* layer) { this->s_foreground = layer; }

	/**
	 * Adds an entity to the scene.
	 *
	 * @param entity
	 *   Entity to be added.
	 */
	void addEntity(Entity* entity) { this->entities.push_back(entity); }

	/**
	 * Removes an entity from the scene.
	 *
	 * @param entity
	 *   Entity to be removed.
	 */
	void removeEntity(Entity* entity);
};

#endif /* RRE_SCENE */
