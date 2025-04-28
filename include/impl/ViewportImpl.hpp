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
	 * Sets scaling factor of viewport renderer.
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
	 * Sets fade in animation.
	 *
	 * @param start_time
	 *   Timestamp when animation should begin.
	 * @param ms
	 *   Duration of animation in milliseconds.
	 */
	virtual void setFadeIn(uint64_t start_time, uint32_t ms) = 0;

	/**
	 * Sets fade out animation.
	 *
	 * @param start_time
	 *   Timestamp when animation should begin.
	 * @param ms
	 *   Duration of animation in milliseconds.
	 */
	virtual void setFadeOut(uint64_t start_time, uint32_t ms) = 0;

	/**
	 * Sets fade in/out color.
	 *
	 * FIXME: not yet supported
	 *
	 * @param r
	 *   Red value.
	 * @param g
	 *   Green value.
	 * @param b
	 *   Blue value.
	 */
	virtual void setFadeColor(uint8_t r, uint8_t g, uint8_t b) = 0;

	/**
	 * Renders the current scene, movie, menu, etc. on viewport.
	 */
	virtual void render() = 0;
};

#endif /* RRE_VIEWPORT_IMPL */
