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
#include "Renderer.hpp"
#include "Sprite.hpp"


/**
 * Animated sprite to be drawn on viewport renderer.
 */
class AnimatedSprite: public Sprite {
private:
	static Logger logger;

	/** Available animation modes of this sprite. */
	std::unordered_map<std::string, Animation> modes;

	/** Animation currently being displayed. */
	Animation* current_mode;

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
	AnimatedSprite(SDL_Texture* texture, uint32_t tile_width, uint32_t tile_height);

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
	 * Adds animation modes to sprite.
	 *
	 * @param modes
	 *   Animation modes mapping.
	 */
	void setModes(std::unordered_map<std::string, Animation> modes) { this->modes = modes; }

	/**
	 * Sets the current animation mode.
	 *
	 * @param id
	 *   Mode identifier. If `id` isn't configured, an uninitialized animation definition is used.
	 */
	void setMode(std::string id) override;

	/**
	 * Retrieves ID of current mode.
	 *
	 * @return
	 *   Mode identifier.
	 */
	std::string getModeId() override {
		if (current_mode) {
			return current_mode->getId();
		}
		return Sprite::getModeId();
	}

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
	void render(Renderer* ctx, uint32_t x, uint32_t y, SDL_RendererFlip flags) override;

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
	Animation* getDefaultMode();
};

#endif /* RRE_ANIMATED_SPRITE */
