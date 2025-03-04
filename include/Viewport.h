/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_VIEWPORT_H
#define RRE_VIEWPORT_H

#include <SDL2/SDL_render.h>

#include "FontMap.h"
#include "GameMode.h"
#include "Logger.h"
#include "Scene.h"
#include "Sprite.h"


class Viewport {
private:
	/** Logger instance for this class. */
	Logger* logger;

	// singleton class
	static Viewport* instance;
	Viewport();
	~Viewport() {}

	// delete copy constructor & assignment operator
	Viewport(const Viewport&) = delete;
	Viewport& operator=(const Viewport&) = delete;

	SDL_Renderer* renderer;
	FontMap* font_map;
	uint16_t current_fps;

	GameMode::Mode mode;

	SDL_Texture* background;
	Scene* scene;

public:
	static Viewport* get() {
		if (instance == nullptr) {
			instance = new Viewport();
		}
		return instance;
	}

	void init(SDL_Window* window);
	void shutdown();
	void setFontMap(FontMap* font_map) { this->font_map = font_map; }
	void setCurrentFPS(uint16_t fps) { this->current_fps = fps; }
	void setScale(uint16_t scale);

	void unsetBackground();
	bool setBackground(std::string path);
	void unsetScene();
	bool setScene(Scene* scene);
	void setMode(GameMode::Mode mode);

	SDL_Renderer* getRenderer() { return this->renderer; }

	// TODO: rename to "drawImage" or "drawTexture"
	void drawSprite(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect);
	void drawSprite(SDL_Texture* texture, SDL_Rect rect) { this->drawSprite(texture, rect, rect); }
	void drawSprite(Sprite* sprite, uint32_t x, uint32_t y);
	void draw();

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
