/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_RENDERER
#define RRE_RENDERER

#include <cstdint> // *int*_t
#include <string>

#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include "Image.hpp"
#include "Logger.hpp"


/**
 * Renderer state that can be saved & restored.
 */
struct RendererState {
	SDL_Color color;
	SDL_BlendMode blend_mode;
};

/**
 * Wrapper for `SDL_Renderer`.
 */
class Renderer {
private:
	static Logger logger;

	/** Actual renderer interface. */
	SDL_Renderer* internal;

	/** Saved state. */
	RendererState* state;

public:
	Renderer();

	~Renderer() {
		SDL_DestroyRenderer(internal);
		internal = nullptr;
		clearState();
	}

	/** Clears current rendering target with drawing color. */
	void clear();

	/** Updates display with any rendering performed since previous call. */
	void present();

	/** Saves renderer state. */
	void save();

	/** Restores renderer to saved state. */
	void restore();

	/**
	 * Draws a rectangle on current rendering target.
	 *
	 * @param rect
	 *   Rectangle dimensions.
	 */
	void drawRect(SDL_Rect rect);

	/**
	 * Draws a rectangle on current rendering target.
	 *
	 * @param x
	 *   Left position on horizontal axis.
	 * @param y
	 *   Top position on vertical axis.
	 * @param width
	 *   Rectangle width.
	 * @param height
	 *   Rectangle height.
	 */
	void drawRect(int32_t x, int32_t y, int32_t width, int32_t height);

	/**
	 * Fills rectangle on current rendering target with drawing color.
	 *
	 * @param rect
	 *   Rectangle dimensions.
	 */
	void fillRect(SDL_Rect rect);

	/**
	 * Fills rectangle on current rendering target with drawing color.
	 *
	 * @param x
	 *   Left position on horizontal axis.
	 * @param y
	 *   Top position on vertical axis.
	 * @param width
	 *   Rectangle width.
	 * @param height
	 *   Rectangle height.
	 */
	void fillRect(int32_t x, int32_t y, int32_t width, int32_t height);

	/**
	 * Draws a texture on rendering target.
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
	void drawTexture(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect, SDL_RendererFlip flags);

	/**
	 * Draws a texture on rendering target.
	 *
	 * @param texture
	 *   Texture reference to draw.
	 * @param s_rect
	 *   Drawing points of source image.
	 * @param t_rect
	 *   Drawing points of target renderer.
	 * @deprecated
	 *   Use `Renderer::drawTexture`.
	 */
	void drawTexture(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect) {
		drawTexture(texture, s_rect, t_rect, SDL_FLIP_NONE);
	}

	/**
	 * Draws a texture on rendering target.
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
	 * Draws a texture on rendering target.
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
	 * Draws an image on rendering target.
	 *
	 * @param img
	 *   Image to be drawn.
	 * @param sx
	 * @param sy
	 * @param s_width
	 * @param s_height
	 * @param x
	 *   Pixel position to draw on horizontal axis.
	 * @param y
	 *   Pixel position to draw on vertical axis.
	 * @param flags
	 *   Flags to flip image horizontally & vertically.
	 */
	void drawImage(Image* img, uint32_t sx, uint32_t sy, uint32_t s_width, uint32_t s_height,
			uint32_t x, uint32_t y, SDL_RendererFlip flags);

	/**
	 * Draws an image on rendering target.
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
	 * Draws an image on rendering target.
	 *
	 * @param img
	 *   Image to be drawn.
	 * @param sx
	 * @param sy
	 * @param s_width
	 * @param s_height
	 * @param x
	 *   Pixel position to draw on horizontal axis.
	 * @param y
	 *   Pixel position to draw on vertical axis.
	 */
	void drawImage(Image* img, uint32_t x, uint32_t y, SDL_RendererFlip flags);

	/**
	 * Draws an image on rendering target.
	 *
	 * @param img
	 *   Image to be drawn.
	 * @param x
	 *   Pixel position to draw on horizontal axis.
	 * @param y
	 *   Pixel position to draw on vertical axis.
	 */
	void drawImage(Image* img, uint32_t x, uint32_t y) { drawImage(img, x, y, SDL_FLIP_NONE); }

	/**
	 * Sets scaling factor of rendering target.
	 *
	 * @param scale
	 *   New scaling factor.
	 */
	void setScale(uint16_t scale);

	/**
	 * Sets blend mode used for drawing operations.
	 *
	 * @param blend_mode
	 *   Blend mode to use.
	 */
	void setBlendMode(SDL_BlendMode blend_mode);

	/**
	 * Sets color used for drawing operations.
	 *
	 * @param r
	 *   Color's red value.
	 * @param g
	 *   Color's green value.
	 * @param b
	 *   Color's blue value.
	 * @param a
	 *   Color's alpha value.
	 */
	void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	/**
	 * Sets color with opaque alpha used for drawing operations.
	 *
	 * @param r
	 *   Color's red value.
	 * @param g
	 *   Color's green value.
	 * @param b
	 *   Color's blue value.
	 */
	void setDrawColor(uint8_t r, uint8_t g, uint8_t b) { setDrawColor(r, g, b, 255); }

	/**
	 * Sets color used for drawing operations.
	 *
	 * @param color
	 *   Color to use.
	 */
	void setDrawColor(SDL_Color color);

	/**
	 * Retrieves color used for drawing operations.
	 *
	 * @return
	 *   RGBA drawing color.
	 */
	SDL_Color getDrawColor();

	/**
	 * Creates a texture from surface.
	 *
	 * @param surface
	 *   Surface reference with pixel data.
	 * @return
	 *   New texture.
	 */
	SDL_Texture* textureFromSurface(SDL_Surface* surface);

	/**
	 * Creates a texture from filesystem resource.
	 *
	 * @param path
	 *   Path to resource file.
	 * @return
	 *   New texture.
	 */
	SDL_Texture* textureFromPath(std::string path);

private:
	/** Clears saved state. */
	void clearState() {
		if (state) {
			delete state;
			state = nullptr;
		}
	}
};

#endif /* RRE_RENDERER */
