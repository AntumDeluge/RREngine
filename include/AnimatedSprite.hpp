/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_ANIMATED_SPRITE
#define RRE_ANIMATED_SPRITE

#include <cstdint> // *int*_t
#include <string>
#include <unordered_map>

#include <SDL2/SDL_render.h>

#include "Animation.hpp"
#include "Logger.hpp"
#include "Sprite.hpp"
#include "ViewportRenderer.hpp"


/**
 * Animated sprite to be drawn on viewport renderer.
 */
class AnimatedSprite: public Sprite {
private:
	static Logger logger;

	/** Available animation modes of this sprite. */
	std::unordered_map<std::string, Animation> modes;

	/** Animation currently being displayed. */
	const Animation* current_mode;

	/** Identifier for sprite's default animation mode. */
	std::string default_mode;

	/** Frame currently being drawn. */
	uint32_t frame_index = 0;
	/** Time when frame animation began. */
	uint64_t frame_start = 0;

public:
	/**
	 * Creates an animated sprite.
	 *
	 * @param texture
	 *   Image texture used for drawing on renderer.
	 */
	AnimatedSprite(SDL_Texture* texture);

	/**
	 * Creates an animated sprite.
	 *
	 * @param texture
	 *   Image texture used for drawing on renderer.
	 * @param tile_width
	 *   Pixel width of this sprite.
	 * @param tile_height
	 *   Pixel height of this sprite.
	 */
	AnimatedSprite(SDL_Texture* texture, uint32_t tile_width, uint32_t tile_height):
		AnimatedSprite(texture) {
		this->tile_width = tile_width;
		this->tile_height = tile_height;
	}

	/**
	 * Creates an animated sprite.
	 *
	 * @param id
	 *   Identifier used to retrieve image texture for drawing on renderer from configuration.
	 */
	AnimatedSprite(std::string id);

	/**
	 * Creates an animated sprite.
	 *
	 * @param id
	 *   Identifier used to retrieve image texture for drawing on renderer from configuration.
	 * @param tile_width
	 *   Pixel width of this sprite.
	 * @param tile_height
	 *   Pixel height of this sprite.
	 */
	AnimatedSprite(std::string id, uint32_t tile_width, uint32_t tile_height): AnimatedSprite(id) {
		this->tile_width = tile_width;
		this->tile_height = tile_height;
	}

	/**
	 * Copy constructor.
	 *
	 * @param other
	 *   Sprite instance to be copied.
	 */
	AnimatedSprite(const AnimatedSprite& other): Sprite(other) {
		modes = other.modes; // FIXME: crashes (uncaught exception of type std::length_error: vector)
		current_mode = other.current_mode;
		default_mode = other.default_mode;
	}

	/**
	 * Default constructor.
	 *
	 * Creates an uninitialized animated sprite.
	 */
	AnimatedSprite(): AnimatedSprite(nullptr) {}

	/** Default destructor. */
	~AnimatedSprite() {
		this->modes.clear();
		this->current_mode = nullptr; // should have been deleted in modes loop
	}

	/**
	 * Adds an animation mode to sprite.
	 *
	 * @param id
	 *   Mode identifier.
	 * @param animation
	 *   Animation definition.
	 */
	void addMode(std::string id, Animation animation) { modes[id] = animation; }

	/**
	 * Sets the current animation mode.
	 *
	 * @param id
	 *   Mode identifier. If `id` isn't configured, an uninitialized animation definition is used.
	 */
	void setMode(std::string id);

	/**
	 * Sets ID of default animation mode.
	 *
	 * @param id
	 *   Mode identifier.
	 */
	void setDefaultMode(std::string id) {
		this->default_mode = id;
	}

	/** Overrides `Sprite.render`. */
	void render(ViewportRenderer* viewport, uint32_t x, uint32_t y) override;

private:
	/**
	 * Checks if current animation should loop playback.
	 *
	 * @return
	 *   `true` if current animation definition is configured to loop.
	 */
	bool loops() {
		return ((Animation*) this->current_mode)->loops();
	}

	/**
	 * Retrieves a reference to the configured default animation mode.
	 *
	 * @return
	 *   Default animation definition or uninitialized animation if default not configured.
	 */
	const Animation* getDefaultMode();
};

#endif /* RRE_ANIMATED_SPRITE */
