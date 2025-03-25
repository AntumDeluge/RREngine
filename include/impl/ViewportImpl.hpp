/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_VIEWPORT_IMPL
#define RRE_VIEWPORT_IMPL

#include <cstdint> // *int*_t

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "FontMap.hpp"
#include "Image.hpp"
#include "enum/GameMode.hpp"


/**
 * Abstract base class for viewport.
 *
 * TODO:
 * - support scaling in draw methods
 */
class ViewportImpl {
protected:
	/** The system renderer. */
	SDL_Renderer* renderer;

public:
	/** Virtual default destructor. */
	virtual ~ViewportImpl() {}

	/**
	 * Initializes the pixel data renderer.
	 *
	 * @param window
	 *   Window where renderer should draw.
	 */
	virtual void init(SDL_Window* window) = 0;

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
	SDL_Renderer* getRenderer() { return this->renderer; }

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
	 * Draws a texture on the renderer.
	 *
	 * @param texture
	 *   Texture reference to draw.
	 * @param s_rect
	 *   Drawing points of source image.
	 * @param t_rect
	 *   Drawing points of target renderer.
	 * @param flags
	 *   Flags to flip image horizontally & vertically.
	 */
	virtual void drawTexture(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect,
			SDL_RendererFlip flags) = 0;

	/**
	 * Draws a texture on the renderer.
	 *
	 * @param texture
	 *   Texture reference to draw.
	 * @param s_rect
	 *   Drawing points of source image.
	 * @param t_rect
	 *   Drawing points of target renderer.
	 */
	void drawTexture(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect) {
		drawTexture(texture, s_rect, t_rect, SDL_FLIP_NONE);
	}

	/**
	 * Draws a texture on the renderer.
	 *
	 * @param texture
	 *   Texture reference.
	 * @param rect
	 *   Drawing points of both source image & target renderer.
	 * @param flags
	 *   Flags to flip image horizontally & vertically.
	 */
	void drawTexture(SDL_Texture* texture, SDL_Rect rect, SDL_RendererFlip flags) {
		drawTexture(texture, rect, rect, flags);
	}

	/**
	 * Draws a texture on the renderer.
	 *
	 * @param texture
	 *   Texture reference.
	 * @param rect
	 *   Drawing points of both source image & target renderer.
	 */
	void drawTexture(SDL_Texture* texture, SDL_Rect rect) {
		drawTexture(texture, rect, rect, SDL_FLIP_NONE);
	}

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
	 * @param flags
	 *   Flags to flip image horizontally & vertically.
	 */
	virtual void drawImage(Image* img, uint32_t sx, uint32_t sy, uint32_t s_width,
			uint32_t t_height, uint32_t x, uint32_t y, SDL_RendererFlip flags) = 0;

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
	void drawImage(Image* img, uint32_t sx, uint32_t sy, uint32_t s_width,
			uint32_t s_height, uint32_t x, uint32_t y) {
		drawImage(img, sx, sy, s_width, s_height, x, y, SDL_FLIP_NONE);
	}

	/**
	 * Draws an image on the viewport.
	 *
	 * @param img
	 *   Image to be drawn.
	 * @param x
	 *   Pixel position to draw on horizontal axis of viewport.
	 * @param y
	 *   Pixel position to draw on vertical axis of viewport.
	 * @param flags
	 *   Flags to flip image horizontally & vertically.
	 */
	virtual void drawImage(Image* img, uint32_t x, uint32_t y, SDL_RendererFlip flags) = 0;

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
	void drawImage(Image* img, uint32_t x, uint32_t y) {
		drawImage(img, x, y, SDL_FLIP_NONE);
	}

	/**
	 * Renders the current scene, movie, menu, etc. on viewport.
	 */
	virtual void render() = 0;
};

#endif /* RRE_VIEWPORT_IMPL */
