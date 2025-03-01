/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "Viewport.h"
#include "config.h"


// initialize singleton instance
Viewport* Viewport::instance = nullptr;

Viewport::Viewport() {
	this->logger = Logger::getLogger("Viewport");
	this->renderer = nullptr;
}

void Viewport::init(SDL_Window* window) {
	if (this->renderer != nullptr) {
		this->logger->warn("Viewport instance already initialized");
		return;
	}

#if RRE_DEBUGGING
	this->logger->debug("Creating Viewport renderer ...");
#endif

	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//~ SDL_SetRenderDrawColor(this->renderer, 0, 0, 20, SDL_ALPHA_OPAQUE);
	//~ SDL_Rect vrect; vrect.x = 0, vrect.y = 0, vrect.w = 256, vrect.h = 240;
	//~ SDL_SetRenderViewport(this->renderer, &vrect);
}

void Viewport::shutdown() {
	SDL_DestroyRenderer(this->renderer);
	this->renderer = nullptr;
}

void Viewport::drawSprite(SDL_Texture* texture, SDL_Rect trect, SDL_Rect srect) {
	if (texture == nullptr) {
		this->logger->error("Sprite drawing error; sprite undefined");
		return;
	}

	SDL_RenderClear(this->renderer);
	SDL_RenderCopy(this->renderer, texture, &trect, &srect);
	SDL_RenderPresent(this->renderer);
}

void Viewport::drawSprite(Sprite* sprite, uint32_t x, uint32_t y) {
	SDL_Rect srect;
	srect.x = x;
	srect.y = y;
	srect.w = sprite->getWidth();
	srect.h = sprite->getHeight();

	this->drawSprite(sprite->getTexture(), srect, srect);
}

void Viewport::draw() {
	this->drawScene();
}

void Viewport::drawScene() {
	this->drawBackground();
	this->drawForeground();
	this->drawEntities();
	this->drawText();
}

void Viewport::drawBackground() {
	// TODO:
}

void Viewport::drawForeground() {
	// TODO:
}

void Viewport::drawEntities() {
	// TODO:
}

void Viewport::drawText() {
	// TODO:
}
