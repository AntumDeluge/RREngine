/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_VIEWPORT_H
#define RRE_VIEWPORT_H

#include <SDL2/SDL_render.h>

#include "Logger.h"


class ViewPort {
private:
	/** Logger instance for this class. */
	Logger* logger;

	// singleton class
	static ViewPort* instance;
	ViewPort();
	~ViewPort() {}

	// delete copy constructor & assignment operator
	ViewPort(const ViewPort&) = delete;
	ViewPort& operator=(const ViewPort&) = delete;

	SDL_Renderer* renderer;

public:
	static ViewPort* get() {
		if (instance == nullptr) {
			instance = new ViewPort();
		}
		return instance;
	}

	void init(SDL_Window* window);
	void shutdown();

	void draw(SDL_Texture* image, SDL_Rect rect);
	SDL_Renderer* getRenderer() { return this->renderer; }
};

#endif /* RRE_VIEWPORT_H */
