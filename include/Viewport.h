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


// TODO: move rendering functions to new renderer class or Scene
class Viewport: public ViewportRenderer {
private:
	/** Logger instance for this class. */
	static Logger logger;

	// singleton class
	static Viewport* instance;
	Viewport();
	// deletion of pointer members handled in Viewport.shutdown
	~Viewport() {}

	// delete copy constructor & assignment operator
	Viewport(const Viewport&) = delete;
	Viewport& operator=(const Viewport&) = delete;

	SDL_Renderer* renderer;
	FontMap* font_map;
	uint16_t current_fps;

	GameMode::Mode mode;

	SDL_Texture* background;
	Sprite* fps_sprite;
	Scene* scene;

	/** Currently playing movie. */
	Movie* movie;

	// TODO: replace with text sprite class with x/y offsets
	std::vector<Sprite*> text_sprites;

public:
	static Viewport* get() {
		if (instance == nullptr) {
			instance = new Viewport();
		}
		return instance;
	}

	static void destroy() {
		if (Viewport::instance != nullptr) {
			Viewport::instance->shutdown();
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

	void setFontMap(FontMap* font_map) { this->font_map = font_map; }
	FontMap* getFontMap() { return this->font_map; }
	void setCurrentFPS(uint16_t fps);
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

	void drawTexture(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect);
	void drawTexture(SDL_Texture* texture, SDL_Rect rect) { this->drawTexture(texture, rect, rect); }

	void drawImage(ImageImpl* img, uint32_t sx, uint32_t sy, uint32_t s_width, uint32_t t_height,
			uint32_t x, uint32_t y) override;
	void drawImage(ImageImpl* img, uint32_t x, uint32_t y) override;

	// TODO: rename to render
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
	// TODO: replace with methods in Scene class
	void drawScene();
	void drawBackground();
	void drawForeground();

	void drawTitle();
	void drawText();
	void drawFPS();
};

#endif /* RRE_VIEWPORT_H */
