/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "ParallaxImage.hpp"


Logger ParallaxImage::logger = Logger::getLogger("ParallaxImage");

void ParallaxImage::render(Renderer* ctx, uint32_t x, uint32_t y) {
	if (orientation == HORIZONTAL) {
		uint32_t width_max = ctx->getInternalWidth();
		uint32_t dx = 0;
		while (dx < width_max) {
			ctx->drawImage(this, dx, 0);
			dx += this->width;
		}
	} else if (orientation == VERTICAL) {
		uint32_t height_max = ctx->getInternalHeight();
		uint32_t dy = 0;
		while (dy < height_max) {
			ctx->drawImage(this, 0, dy);
			dy += this->height;
		}
	} else {
		uint32_t width_max = ctx->getInternalWidth();
		uint32_t height_max = ctx->getInternalHeight();
		uint32_t dx = 0;
		while (dx < width_max) {
			uint32_t dy = 0;
			while (dy < height_max) {
				ctx->drawImage(this, dx, dy);
				dy += this->height;
			}
			dx += this->width;
		}
	}
}
