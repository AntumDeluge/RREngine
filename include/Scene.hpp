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

#include "Logger.hpp"
#include "Object.hpp"
#include "SceneImpl.hpp"
#include "Tileset.hpp"
#include "ViewportRenderer.hpp"


/**
 * Class to represent a scene being drawn on the viewport.
 *
 * TODO:
 * - need collision mapping to match collision layer
 * - support additional background with parallax scrolling
 * - create separate class called SceneBuilder to serve as framework to rendering scene
 * - don't use pointers for layers
 * - defined a SceneLayer class that can support animation
 *
 * FIXME: for parallax scrolling background layer 1, it might be better to use a full image instead
 *        of a tiling image layer
 */
class Scene: public SceneImpl {
private:
	static Logger logger;

	uint32_t width;
	uint32_t height;

	/** Individual tile pixel width. */
	uint32_t tile_width;
	/** Individual tile pixel height. */
	uint32_t tile_height;

	/** Scene tilesets. */
	std::vector<Tileset*> tilesets;

	/** Parallax scrolling background layer 1. */
	tmx::ImageLayer* s_background;
	/** Parallax scrolling background layer 2. */
	tmx::ImageLayer* s_background2;

	// TODO: use LayerDefinition type

	/** Bottom tiled layer. */
	std::vector<uint32_t> background;
	/** Terrain layer drawn under entities. */
	std::vector<uint32_t> terrain;
	/** Entities located in scene. */
	std::vector<uint32_t> objects_layer;
	/** Terrain layer containing collision info. */
	std::vector<uint32_t> collision;
	/** Top tiled layer drawn over entities. */
	std::vector<uint32_t> foreground;

	/** Parallax scrolling foreground layer. */
	tmx::ImageLayer* s_foreground;

	/** Objects currently occupying this scene. */
	std::vector<Object*> objects;

	/** ID of next object to be added to scene. */
	uint32_t next_object_id;

public:
	/**
	 * Creates a new scene.
	 *
	 * @param tile_width
	 *   Individual tile pixel width.
	 * @param tile_height
	 *   Individual tile pixel height.
	 */
	Scene(uint32_t width, uint32_t height, uint32_t tile_width, uint32_t tile_height) {
		this->width = width;
		this->height = height;
		this->tile_width = tile_width;
		this->tile_height = tile_height;

		this->s_background = nullptr;
		this->s_background2 = nullptr;
		this->s_foreground = nullptr;

		next_object_id = 1;
	}

	/** Default destructor. */
	~Scene() {
		delete this->s_background;
		this->s_background = nullptr;
		delete this->s_background2;
		this->s_background2 = nullptr;
		delete this->s_foreground;
		this->s_foreground = nullptr;

		// NOTE: should objects by shared_ptr & destroyed automatically?
		for (Object* obj: this->objects) {
			delete obj;
			obj = nullptr;
		}
		this->objects.clear();

		for (Tileset* ts: tilesets) {
			delete ts;
			ts = nullptr;
		}
		tilesets.clear();
	}

	/**
	 * Adds a tileset to use in scene.
	 *
	 * @param tileset
	 *   Tileset to be added.
	 */
	void addTileset(Tileset* tileset) {
		this->tilesets.push_back(tileset);
	}

	/**
	 * Draws scene on renderer.
	 *
	 * @param viewport
	 *   Viewport renderer.
	 */
	void render(ViewportRenderer* viewport) override;

	/**
	 * Draws a tile layer on renderer.
	 *
	 * TODO:
	 * - build single image for rendering from tiles before drawing instead of drawing individual tiles (excluding animated ones)
	 * - support flipped tiles
	 *
	 * @param viewport
	 *   Viewport renderer.
	 * @param gids
	 *   Layer definition.
	 */
	void renderTileLayer(ViewportRenderer* viewport, std::vector<uint32_t> gids);

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
	void setLayerBackground(std::vector<uint32_t> layer) { background = layer; };

	/**
	 * Sets layer to use for terrain.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerTerrain(std::vector<uint32_t> layer) { terrain = layer; }

	/**
	 * Sets layer to use for objects.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerObjects(std::vector<uint32_t> layer) { objects_layer = layer; }

	/**
	 * Sets layer to use for collision.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerCollision(std::vector<uint32_t> layer) { collision = layer; }

	/**
	 * Sets layer to use for foreground.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerForeground(std::vector<uint32_t> layer) { foreground = layer; }

	/**
	 * Sets layer to use for scrolling foreground.
	 *
	 * @param layer
	 *   Image layer definition.
	 */
	void setLayerSForeground(tmx::ImageLayer* layer) { this->s_foreground = layer; }

	/**
	 * Adds an object to the scene.
	 *
	 * @param obj
	 *   Object to be added.
	 */
	void addObject(Object* obj);

	/**
	 * Removes an object from the scene.
	 *
	 * @param obj
	 *   Object to be removed.
	 */
	void removeObject(Object* obj);
};

#endif /* RRE_SCENE */
