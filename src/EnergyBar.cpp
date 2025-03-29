/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "EnergyBar.hpp"


Logger EnergyBar::logger = Logger::getLogger("EnergyBar");

void EnergyBar::setOuterColor(uint8_t r, uint8_t g, uint8_t b) {
	color_outer.r = r;
	color_outer.g = g;
	color_outer.b = b;
	color_outer.a = 255;
}

void EnergyBar::setInnerColor(uint8_t r, uint8_t g, uint8_t b) {
	color_inner.r = r;
	color_inner.g = g;
	color_inner.b = b;
	color_inner.a = 255;
}

void EnergyBar::render(Renderer* ctx, int32_t energy) {
	uint32_t height = 56;

	ctx->save();
	// black background
	ctx->setDrawColor(0, 0, 0);
	ctx->fillRect(x, y, 8, height);

	int32_t offset_y = -2;
	for (int32_t seg = 0; seg < base_energy; seg++) {
		ctx->setDrawColor(color_outer);
		ctx->fillRect(x + 1, y + height + offset_y, 6, 1);
		ctx->setDrawColor(color_inner);
		ctx->fillRect(x + 3, y + height + offset_y, 2, 1);

		offset_y -= 2;
	}

	ctx->restore();
}
