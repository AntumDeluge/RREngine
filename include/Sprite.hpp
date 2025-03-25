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

#include "Image.hpp"
#include "Logger.hpp"
#include "impl/ViewportImpl.hpp"


/**
 * Sprite interface class.
 */
class Sprite: public Image {
private:
	static Logger logger;

	/** Timestamp at which this sprite should no longer be drawn on renderer. */
	uint32_t expires = 0;

protected:
	/** Visual pixel width. */
	uint32_t tile_width;
	/** Visual pixel height. */
	uint32_t tile_height;

	/** Image tile index that should be drawn. */
	uint32_t tile_index;

public:
	/**
	 * Creates a new sprite.
	 *
	 * @param texture
	 *   Image texture used for drawing on renderer.
	 */
	Sprite(SDL_Texture* texture): Image(texture) {
		tile_width = width;
		tile_height = height;
		tile_index = 0;
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
	 * @param tile_index
	 *   Image tile index that should be drawn.
	 */
	Sprite(SDL_Texture* texture, uint32_t tile_width, uint32_t tile_height, uint32_t tile_index)
	: Sprite(texture) {
		this->tile_width = tile_width;
		this->tile_height = tile_height;
		this->tile_index = tile_index;
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
	 * @param tile_index
	 *   Image tile index that should be drawn.
	 */
	Sprite(std::string id, uint32_t tile_width, uint32_t tile_height, uint32_t tile_index)
	: Sprite(id) {
		this->tile_width = tile_width;
		this->tile_height = tile_height;
		this->tile_index = tile_index;
	}

	/** Default constructor. */
	Sprite(): Image() {
		tile_width = 0;
		tile_height = 0;
		tile_index = 0;
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
	 * Updates tile index to be drawn.
	 *
	 * @param index
	 *   New tile index.
	 */
	void setTileIndex(uint32_t index) { tile_index = index; }

	/**
	 * Does nothing in this implementation. Inheriting classes can override.
	 *
	 * @param id
	 */
	virtual void setMode(std::string id) {
		// does nothing in this implemention
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
	 * @param flags
	 *   Flags to flip image horizontally & vertically.
	 */
	virtual void render(ViewportImpl* viewport, uint32_t x, uint32_t y, SDL_RendererFlip flags);

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
	virtual void render(ViewportImpl* viewport, uint32_t x, uint32_t y) {
		render(viewport, x, y, SDL_FLIP_NONE);
	}
};

#endif /* RRE_SPRITE_H */
