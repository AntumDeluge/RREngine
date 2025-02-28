/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <iostream>

#include "Logger.h"
#include "viewport.h"


bool initialized = false;

// initialize singleton instance
ViewPort* ViewPort::instance = nullptr;

ViewPort::ViewPort() {
	//~ this->renderer = nullptr;
}

void ViewPort::init(SDL_Window* window) {
	Logger* logger = Logger::getLogger("ViewPort");

	//~ if (this->renderer != nullptr) {
	if (initialized) {
		logger->warn("ViewPort instance already initialized");
		return;
	}
	initialized = true;

	logger->debug("Creating ViewPort renderer ...");

	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//~ SDL_SetRenderDrawColor(this->renderer, 0, 0, 20, SDL_ALPHA_OPAQUE);
	//~ SDL_Rect vrect; vrect.x = 0, vrect.y = 0, vrect.w = 256, vrect.h = 240;
	//~ SDL_SetRenderViewport(this->renderer, &vrect);
}

void ViewPort::shutdown() {
	SDL_DestroyRenderer(this->renderer);
	this->renderer = nullptr;
}

void ViewPort::draw(SDL_Texture* image, SDL_Rect srect) {
	// DEBUG:
	//~ std::cout << "width: " << srect.w << ", height: " << srect.h << ", x: " << srect.x << ", y: " << srect.y << std::endl;

	SDL_Rect trect;
	trect.x = 0;
	trect.y = 0;
	trect.w = 256;
	trect.h = 240;

	SDL_RenderClear(this->renderer);
	SDL_RenderCopy(this->renderer, image, &trect, &srect);
	SDL_RenderPresent(this->renderer);
}
