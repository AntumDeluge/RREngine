/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_VIEWPORT_IMPL
#define RRE_VIEWPORT_IMPL

#include <cstdint> // *int*_t

#include "FontMap.hpp"
#include "Renderer.hpp"
#include "enum/GameMode.hpp"


/**
 * Abstract base class for viewport.
 *
 * TODO:
 * - support scaling in draw methods
 */
class ViewportImpl {
public:
	/** Virtual default destructor. */
	virtual ~ViewportImpl() {}

	/**
	 * Cleans up renderer & data memory.
	 */
	virtual void shutdown() = 0;

	/**
	 * Retrieves the viewport renderer where pixel data is drawn.
	 *
	 * @return
	 *   SDL_Renderer instance.
	 */
	virtual Renderer* getRenderer() = 0;

	/**
	 * Sets font map to use for drawing text.
	 *
	 * @param font_map
	 *   New font map.
	 */
	virtual void setFontMap(FontMap* font_map) = 0;

	/**
	 * Retrieves the font map used for drawing text.
	 *
	 * @return
	 *   Current font map instance.
	 */
	virtual FontMap* getFontMap() = 0;

	/**
	 * Updates FPS value.
	 *
	 * @param fps
	 *   Detected FPS.
	 */
	virtual void setCurrentFPS(uint32_t fps) = 0;

	/**
	 * Sets scaling factor of game window.
	 *
	 * @param scale
	 *   New scaling factor.
	 */
	virtual void setScale(uint16_t scale) = 0;

	/**
	 * Sets drawing mode.
	 *
	 * @param mode
	 *   Game mode use to determine how to execute drawing instructions.
	 */
	virtual void setRenderMode(GameMode::Mode mode) = 0;

	/**
	 * Renders the current scene, movie, menu, etc. on viewport.
	 */
	virtual void render() = 0;
};

#endif /* RRE_VIEWPORT_IMPL */
