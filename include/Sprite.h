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

#include "ImageImpl.h"
#include "Logger.h"
#include "ViewportRenderer.h"


/**
 * Sprite interface class.
 */
class Sprite: public ImageImpl {
private:
	static Logger logger;

	/** Timestamp at which this sprite should no longer be drawn on renderer. */
	uint32_t expires = 0;

public:
	/**
	 * Creates a new sprite.
	 *
	 * @param texture
	 *   Image texture used for drawing on renderer.
	 */
	Sprite(SDL_Texture* texture): ImageImpl(texture) {}

	/**
	 * Creates a new sprite.
	 *
	 * @param id
	 *   Identifier used to retrieve image texture for drawing on renderer from configuration.
	 */
	Sprite(std::string id);

	/** Default constructor. */
	Sprite(): Sprite(nullptr) {}

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
	void render(ViewportRenderer* viewport, uint16_t x, uint16_t y);
};

#endif /* RRE_SPRITE_H */
