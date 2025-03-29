/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "Sprite.hpp"


Logger Sprite::logger = Logger::getLogger("Sprite");

void Sprite::render(Renderer* ctx, uint32_t x, uint32_t y, SDL_RendererFlip flags) {
	if (!ready()) {
		logger.warn("Sprite texture not ready");
		return;
	}

	uint32_t cols = width / tile_width;
	uint32_t index_x = tile_index % cols;
	uint32_t index_y = tile_index / cols;

	ctx->drawImage(this, index_x*tile_width, index_y*tile_height, tile_width, tile_height, x, y,
			flags);
}
