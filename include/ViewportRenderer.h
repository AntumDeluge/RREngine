/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_VIEWPORT_RENDERER
#define RRE_VIEWPORT_RENDERER

#include <cstdint> // uint*_t

#include "ImageImpl.h"


/**
 * Abstract base class for viewport.
 *
 * TODO: support scaling in draw methods
 */
class ViewportRenderer {
public:
	/** Virtual default destructor. */
	virtual ~ViewportRenderer() {}

	/**
	 * Draws an image on the viewport.
	 *
	 * @param img
	 *   Image to be drawn.
	 * @param sx
	 * @param sy
	 * @param s_width
	 * @param s_height
	 * @param x
	 *   Pixel position to draw on horizontal axis of viewport.
	 * @param y
	 *   Pixel position to draw on vertical axis of viewport.
	 */
	virtual void drawImage(ImageImpl* img, uint32_t sx, uint32_t sy, uint32_t s_width,
			uint32_t t_height, uint32_t x, uint32_t y) = 0;

	/**
	 * Draws an image on the viewport.
	 *
	 * @param img
	 *   Image to be drawn.
	 * @param x
	 *   Pixel position to draw on horizontal axis of viewport.
	 * @param y
	 *   Pixel position to draw on vertical axis of viewport.
	 */
	virtual void drawImage(ImageImpl* img, uint32_t x, uint32_t y) = 0;
};

#endif /* RRE_VIEWPORT_RENDERER */
