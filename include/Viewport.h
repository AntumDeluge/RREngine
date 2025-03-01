/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_VIEWPORT_H
#define RRE_VIEWPORT_H

#include <SDL2/SDL_render.h>

#include "Logger.h"
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

public:
	static Viewport* get() {
		if (instance == nullptr) {
			instance = new Viewport();
		}
		return instance;
	}

	void init(SDL_Window* window);
	void shutdown();

	SDL_Renderer* getRenderer() { return this->renderer; }

	void drawSprite(SDL_Texture* texture, SDL_Rect trect, SDL_Rect srect);
	void drawSprite(Sprite* sprite, uint32_t x, uint32_t y);
	void draw();

private:
	void drawScene();
	void drawBackground();
	void drawForeground();
	void drawEntities();
	void drawText();
};

#endif /* RRE_VIEWPORT_H */
