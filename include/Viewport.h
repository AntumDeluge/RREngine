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
#include "Scene.h"
#include "Sprite.h"


class Viewport {
private:
	/** Logger instance for this class. */
	// TODO: make static
	Logger logger;

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

	// TODO: replace with text sprite class with x/y offsets
	std::vector<Sprite*> text_sprites;

public:
	static Viewport* get() {
		if (instance == nullptr) {
			instance = new Viewport();
		}
		return instance;
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

	// TODO: rename to "drawImage" or "drawTexture"
	void drawTexture(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect);
	void drawTexture(SDL_Texture* texture, SDL_Rect rect) { this->drawTexture(texture, rect, rect); }
	void drawImage(ImageImpl* sprite, uint32_t x, uint32_t y);
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
	void drawScene();
	void drawBackground();
	void drawForeground();
	void drawEntities();
	void drawTitle();
	void drawText();
	void drawFPS();
};

#endif /* RRE_VIEWPORT_H */
