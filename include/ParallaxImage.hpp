/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_PARALLAX_IMAGE
#define RRE_PARALLAX_IMAGE

#include <cstdint> // *int*_t

#include <SDL2/SDL_render.h>

#include "Image.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"


/** Scrolling axis enumeration. */
enum ORIENT {
	HORIZONTAL,
	VERTICAL,
	ALL
};

/**
 * Represents an image that scrolls at specified rate.
 */
class ParallaxImage: public Image {
private:
	static Logger logger;

	/** Scrolling direction. */
	ORIENT orientation;

public:
	/**
	 * Creates a new parallax image.
	 *
	 * @param texture
	 *   Texture to draw with renderer.
	 */
	ParallaxImage(SDL_Texture* texture): Image(texture) {
		orientation = HORIZONTAL;
	}

	/**
	 * Sets scrolling axis.
	 *
	 * @param orient
	 *   Horizontal and/or vertical axis.
	 */
	void setOrientation(ORIENT orient) {
		orientation = orient;
	}

	/**
	 * Draws image on renderer.
	 *
	 * @param ctx
	 *   Drawing renderer.
	 * @param x
	 *   Player horizontal position.
	 * @param y
	 *   Player vertical position.
	 */
	void render(Renderer* ctx, uint32_t x, uint32_t y);
};

#endif /* RRE_PARALLAX_IMAGE */
