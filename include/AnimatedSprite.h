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
#include "Logger.h"
#include "Sprite.h"
#include "ViewportRenderer.h"


/**
 * Animated sprite to be drawn on viewport renderer.
 *
 * TODO: rename file to AnimatedSprite.hpp
 */
class AnimatedSprite: public Sprite {
private:
	static Logger logger;

	/** Available animation modes of this sprite. */
	std::unordered_map<std::string, const Animation> modes;

	/** Animation currently being displayed. */
	Animation* current_mode;

	/** Identifier for sprite's default animation mode. */
	std::string default_mode;

	/** Frame currently being drawn. */
	uint16_t frame_index = 0;
	/** Time when frame animation began. */
	uint32_t frame_start = 0;

public:
	/**
	 * Creates an animated sprite.
	 *
	 * @param texture
	 *   Image texture used for drawing.
	 */
	AnimatedSprite(SDL_Texture* texture);

	/**
	 * Creates an animated sprite.
	 *
	 * @param id
	 *   Texture identifier used to load from configuration.
	 */
	AnimatedSprite(std::string id);

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
	void addMode(std::string id, const Animation animation) { modes[id] = animation; }

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

	/**
	 * Overrides `Sprite.render`
	 */
	void render(ViewportRenderer* viewport, uint16_t x, uint16_t y);

private:
	/**
	 * Checks if current animation should loop playback.
	 *
	 * @return
	 *   `true` if current animation definition is configured to loop.
	 */
	bool loops() {
		return this->current_mode->loop;
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
