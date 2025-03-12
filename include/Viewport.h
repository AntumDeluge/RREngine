/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_VIEWPORT_H
#define RRE_VIEWPORT_H

#include <vector>

#include <SDL2/SDL_render.h>

#include "FontMap.h"
#include "GameMode.h"
#include "ImageImpl.h"
#include "Logger.h"
#include "Movie.h"
#include "MovieFactory.h"
#include "Scene.h"
#include "Sprite.h"
#include "ViewportRenderer.h"


/**
 * Interface for rendering images.
 *
 * TODO:
 * - move rendering functions to new renderer class or Scene
 * - rename file to Viewport.hpp
 */
class Viewport: public ViewportRenderer {
private:
	/** Logger instance for this class. */
	static Logger logger;

	/** Static singleton instance. */
	static Viewport* instance;

	/** Default constructor. */
	Viewport();

	/**
	 * Default destructor.
	 *
	 * NOTE: deletion of pointer members handled in `Viewport.shutdown`
	 */
	~Viewport() {}

	// delete copy constructor & assignment operator for singleton
	Viewport(const Viewport&) = delete;
	Viewport& operator=(const Viewport&) = delete;

	/** The system renderer. */
	SDL_Renderer* renderer;
	/** Font map for drawing text. */
	FontMap* font_map;
	/** Detected FPS. */
	uint16_t current_fps;

	/**
	 * Current game mode.
	 *
	 * TODO: _maybe_ use `GameLoop.getMode` instead
	 */
	GameMode::Mode mode;

	/** Texture drawn on background during `GameMode::MENU` or `GameMode::TITLE`. */
	SDL_Texture* background;
	/** Text sprite representing RPS that can be drawn on renderer. */
	Sprite* fps_sprite;
	/** Scene rendered during `GameMode::SCENE`. */
	Scene* scene;

	/** Currently playing movie. */
	Movie* movie;

	/**
	 * Text sprite to draw on renderer.
	 *
	 * TODO: replace with text sprite class with x/y offsets
	 */
	std::vector<Sprite*> text_sprites;

public:
	/**
	 * Initializes & retrieves singleton instance.
	 *
	 * @return
	 *   Static singleton instance.
	 */
	static Viewport* get() {
		if (instance == nullptr) {
			instance = new Viewport();
		}
		return instance;
	}

	/** Cleans up viewport initializations. */
	static void destroy() {
		if (Viewport::instance != nullptr) {
			Viewport::instance->shutdown();
			// FIXME: segmentation fault?
			delete Viewport::instance;
		}
		Viewport::instance = nullptr;
	}

	/**
	 * Initializes the pixel data renderer.
	 *
	 * @param window
	 *   Window where renderer should draw.
	 */
	void init(SDL_Window* window);

	/**
	 * Cleans up renderer & data memory.
	 */
	void shutdown();

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
	void setFontMap(FontMap* font_map) { this->font_map = font_map; }

	/**
	 * Retrieves the font map used for drawing text.
	 *
	 * @return
	 *   Current font map instance.
	 */
	FontMap* getFontMap() { return this->font_map; }

	/**
	 * Updates FPS value.
	 *
	 * @param fps
	 *   Detected FPS.
	 */
	void setCurrentFPS(uint32_t fps);

	/**
	 * Sets scaling factor of game window.
	 *
	 * @param scale
	 *   New scaling factor.
	 */
	void setScale(uint16_t scale);

	/**
	 * Unsets background texture.
	 */
	void unsetBackground();

	/**
	 * Sets background texture to draw.
	 *
	 * @param rdpath
	 *   Path to image file relative to data directory (excluding .png suffix).
	 * @return
	 *   `true` if a texture was set.
	 */
	bool setBackground(std::string rdpath);

	/**
	 * Unsets scene data.
	 */
	void unsetScene();

	/**
	 * Sets current scene data.
	 *
	 * @param id
	 *   Scene identifier.
	 * @return
	 *   `true` if scene was set.
	 */
	bool setScene(std::string id);

	/**
	 * Sets drawing mode.
	 *
	 * TODO: rename to "setDrawMode"
	 *
	 * @param mode
	 *   Game mode use to determine how to execute drawing instructions.
	 */
	void setMode(GameMode::Mode mode);

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
	void drawTexture(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect);

	/**
	 * Draws a texture on the renderer.
	 *
	 * @param texture
	 *   Texture reference.
	 * @param rect
	 *   Drawing points of both source image & target renderer.
	 */
	void drawTexture(SDL_Texture* texture, SDL_Rect rect) { this->drawTexture(texture, rect, rect); }

	/**
	 * Draws an image on the renderer.
	 *
	 * @param img
	 *   Image reference.
	 * @param sx
	 * @param xy
	 * @param s_width
	 * @param s_height
	 * @param x
	 *   Left-most point to draw on renderer.
	 * @param y
	 *   Top-most point to draw on renderer.
	 */
	void drawImage(ImageImpl* img, uint32_t sx, uint32_t sy, uint32_t s_width, uint32_t t_height,
			uint32_t x, uint32_t y) override;

	/**
	 * Draw an image on the renderer.
	 *
	 * @param img
	 *   Image reference.
	 * @param x
	 *   Left-most point to draw on renderer.
	 * @param y
	 *   Top-most point to draw on renderer.
	 */
	void drawImage(ImageImpl* img, uint32_t x, uint32_t y) override;

	/**
	 * Renders the current scene, movie, menu, etc. on viewport.
	 *
	 * TODO: rename to render
	 */
	void draw();

	/**
	 * Adds a text sprite to be drawn in viewport.
	 *
	 * @param text
	 *   Text value.
	 */
	void addText(std::string text);

	/**
	 * Clears all text sprites from viewport.
	 */
	void clearText();

private:
	/**
	 * Renders current scene on viewport.
	 *
	 * TODO: replace with methods in Scene class
	 */
	void drawScene();

	/** Renders current background image on viewport. */
	void drawBackground();

	/** Renders current foreground image on viewport. */
	void drawForeground();

	/** Renders configured title menu on viewport. */
	void drawTitle();

	/** Renders text sprites on viewport. */
	void drawText();

	/** Renders FPS text sprite on viewport. */
	void drawFPS();
};

#endif /* RRE_VIEWPORT_H */
