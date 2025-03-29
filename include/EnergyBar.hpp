/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_ENERGY_BAR
#define RRE_ENERGY_BAR

#include <cstdint> // *int*_t

#include <SDL2/SDL_pixels.h>

#include "Logger.hpp"
#include "Renderer.hpp"


/**
 * Class representing an entity's energy drawn on viewport.
 */
class EnergyBar {
private:
	static Logger logger;

	/**
	 * Maximum number of energy lines that can be drawn.
	 */
	int32_t base_energy;

	/** Horizontal position on viewport. */
	uint32_t x;
	/** Vertical position on viewport. */
	uint32_t y;

	/** Outer color of each energy line. */
	SDL_Color color_outer;
	/** Inner color of each energy line. */
	SDL_Color color_inner;

public:
	/**
	 * Creates a new energy bar.
	 *
	 * @param base_energy
	 *   Maximum number of energy lines that can be drawn.
	 * @param x
	 *   Horizontal position on viewport.
	 * @param y
	 *   Vertical position on viewport.
	 */
	EnergyBar(int32_t base_energy, uint32_t x, uint32_t y): base_energy(base_energy), x(x), y(y) {}

	/** Default destructor. */
	~EnergyBar() {}

	/**
	 * Copy constructor.
	 *
	 * @param other
	 *   Energy bar to be copied.
	 */
	EnergyBar(const EnergyBar& other) {
		base_energy = other.base_energy;
		x = other.x;
		y = other.y;
		color_outer = other.color_outer;
		color_inner = other.color_inner;
	}

	/**
	 * Sets drawing position of energy bar.
	 *
	 * @param x
	 *   Horizontal pixel position.
	 * @param y
	 *   Vertical pixel position.
	 */
	void setPos(uint32_t x, uint32_t y) { this->x = x; this->y = y; }

	/**
	 * Sets outer color of each energy line.
	 *
	 * @param r
	 *   Color's red value.
	 * @param g
	 *   Color's green value.
	 * @param b
	 *   Color's blue value.
	 */
	void setOuterColor(uint8_t r, uint8_t g, uint8_t b);

	/**
	 * Sets inner color of each energy line.
	 *
	 * @param r
	 *   Color's red value.
	 * @param g
	 *   Color's green value.
	 * @param b
	 *   Color's blue value.
	 */
	void setInnerColor(uint8_t r, uint8_t g, uint8_t b);

	/**
	 * Draws energy bar on rendering target.
	 *
	 * @param ctx
	 *   Rendering context.
	 * @param energy
	 *   Number of energy lines to draw.
	 */
	void render(Renderer* ctx, int32_t energy);
};

#endif /* RRE_ENERGY_BAR */
