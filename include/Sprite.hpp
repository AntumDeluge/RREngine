/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SPRITE_H
#define RRE_SPRITE_H

#include <cstdint> // uint*_t
#include <string>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include "ImageImpl.hpp"
#include "Logger.hpp"
#include "ViewportRenderer.hpp"


/**
 * Sprite interface class.
 */
class Sprite: public ImageImpl {
private:
	static Logger logger;

	/** Timestamp at which this sprite should no longer be drawn on renderer. */
	uint32_t expires = 0;

protected:
	/** Visual pixel width. */
	uint32_t tile_width;
	/** Visual pixel height. */
	uint32_t tile_height;

public:
	/**
	 * Creates a new sprite.
	 *
	 * @param texture
	 *   Image texture used for drawing on renderer.
	 */
	Sprite(SDL_Texture* texture): ImageImpl(texture) {
		tile_width = width;
		tile_height = height;
	}

	/**
	 * Creates a new sprite.
	 *
	 * @param texture
	 *   Image texture used for drawing on renderer.
	 * @param tile_width
	 *   Pixel width of this sprite.
	 * @param tile_height
	 *   Pixel height of this sprite.
	 */
	Sprite(SDL_Texture* texture, uint32_t tile_width, uint32_t tile_height): Sprite(texture) {
		this->tile_width = tile_width;
		this->tile_height = tile_height;
	}

	/**
	 * Creates a new sprite.
	 *
	 * @param id
	 *   Identifier used to retrieve image texture for drawing on renderer from configuration.
	 */
	Sprite(std::string id);

	/**
	 * Creates a new sprite.
	 *
	 * @param id
	 *   Identifier used to retrieve image texture for drawing on renderer from configuration.
	 * @param tile_width
	 *   Pixel width of this sprite.
	 * @param tile_height
	 *   Pixel height of this sprite.
	 */
	Sprite(std::string id, uint32_t tile_width, uint32_t tile_height): Sprite(id) {
		this->tile_width = tile_width;
		this->tile_height = tile_height;
	}

	/** Default constructor. */
	Sprite(): ImageImpl() {
		tile_width = 0;
		tile_height = 0;
	}

	/**
	 * Sets sprite expiration.
	 *
	 * @param expires
	 *   Timestamp at which this sprite should no longer be drawn on renderer.
	 */
	void setExpiration(uint32_t expires) {
		this->expires = expires;
	}

	/**
	 * Checks if the sprite has expired.
	 *
	 * @return
	 *   `true` if current time is at least the same as expiration timestamp.
	 */
	bool expired() {
		return this->expires != 0 && SDL_GetTicks64() >= this->expires;
	}

	/**
	 * Draws this sprite on the viewport.
	 *
	 * @param viewport
	 *   Viewport render instance.
	 * @param x
	 *   Pixel drawing position on horizontal axis.
	 * @param y
	 *   Pixel drawing position on vertical axis.
	 */
	void render(ViewportRenderer* viewport, uint32_t x, uint32_t y);
};

#endif /* RRE_SPRITE_H */
