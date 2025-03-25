/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SCENE
#define RRE_SCENE

#include <vector>

#include <SDL2/SDL_rect.h>
#include <tmxlite/ImageLayer.hpp>

#include "LayerDefinition.hpp"
#include "Logger.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Tileset.hpp"
#include "ViewportRenderer.hpp"
#include "impl/SceneImpl.hpp"


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

	/** Collision mappings defined by collision layer. */
	std::vector<std::vector<uint8_t>> collision_map;

	/** Scene tilesets. */
	std::vector<Tileset*> tilesets;

	/** Parallax scrolling background layer 1. */
	tmx::ImageLayer* s_background;
	/** Parallax scrolling background layer 2. */
	tmx::ImageLayer* s_background2;

	/** Bottom tiled layer. */
	LayerDefinition background;
	/** Terrain layer drawn under entities. */
	LayerDefinition terrain;
	/** Entities located in scene. */
	LayerDefinition objects_layer;
	/** Terrain layer containing collision info. */
	LayerDefinition collision;
	/** Top tiled layer drawn over entities. */
	LayerDefinition foreground;

	/** Parallax scrolling foreground layer. */
	tmx::ImageLayer* s_foreground;

	/** Objects currently occupying this scene. */
	std::vector<Object*> objects;

	/** Active player in this scene. */
	Player* player;

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

		collision_map = std::vector<std::vector<uint8_t>>(this->height, std::vector<uint8_t>(this->width, 0));

		this->s_background = nullptr;
		this->s_background2 = nullptr;
		this->s_foreground = nullptr;

		this->player = nullptr;

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

		// FIXME: player deletion should be handled by shutdown to prevent data loss when scene ends
		if (player != nullptr) {
			delete player;
			player = nullptr;
		}
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

	/** Called every game logic step. */
	void logic() override;

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
	void renderTileLayer(ViewportRenderer* viewport, LayerDefinition ldef);

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
	void setLayerBackground(LayerDefinition ldef) { background = ldef; };

	/**
	 * Sets layer to use for terrain.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerTerrain(LayerDefinition ldef) { terrain = ldef; }

	/**
	 * Sets layer to use for objects.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerObjects(LayerDefinition ldef) { objects_layer = ldef; }

	/**
	 * Sets layer to use for collision.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerCollision(LayerDefinition ldef);

	/**
	 * Sets layer to use for foreground.
	 *
	 * @param layer
	 *   Tile layer definition.
	 */
	void setLayerForeground(LayerDefinition ldef) { foreground = ldef; }

	/**
	 * Sets layer to use for scrolling foreground.
	 *
	 * @param layer
	 *   Image layer definition.
	 */
	void setLayerSForeground(tmx::ImageLayer* layer) { this->s_foreground = layer; }

	/**
	 * Adds a point of collision to map.
	 *
	 * @param x
	 * @param y
	 */
	void setCollisionPoint(uint32_t x, uint32_t y) { collision_map[x][y] = 1; }

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

	/**
	 * Adds a player to this scene.
	 *
	 * @param player
	 *   Player to be added.
	 */
	void addPlayer(Player* player);

	/**
	 * Retrieves active player in this scene.
	 *
	 * @return
	 *   Player instance or `null` if no player is set.
	 */
	Player* getPlayer() { return player; }

	/** Overrides `SceneImpl.getGravity`. */
	float getGravity(uint32_t x, uint32_t y) override;

	/** Overrides `SceneImpl.collidesGround`. */
	bool collidesGround(SDL_Rect rect) override;

	/** Overrides `SceneImple.collidesWall`. */
	bool collidesWall(SDL_Rect rect) override;
};

#endif /* RRE_SCENE */
