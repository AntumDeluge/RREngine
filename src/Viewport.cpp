/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

//~ #include <string>

#include "Viewport.h"
#include "config.h"

//~ using namespace std;


// initialize singleton instance
Viewport* Viewport::instance = nullptr;

Viewport::Viewport() {
	this->logger = Logger::getLogger("Viewport");
	this->renderer = nullptr;
	// TODO: initial viewport font should be configured in game.xml
	this->font_map = nullptr; // cannot be set here because font maps have not yet loaded
	this->current_fps = 0;
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

void Viewport::drawSprite(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect) {
	if (texture == nullptr) {
		this->logger->error("Sprite drawing error; sprite undefined");
		return;
	}

	SDL_RenderCopy(this->renderer, texture, &s_rect, &t_rect);
}

void Viewport::drawSprite(Sprite* sprite, uint32_t x, uint32_t y) {
	SDL_Rect s_rect;
	s_rect.x = x;
	s_rect.y = y;
	s_rect.w = sprite->getWidth();
	s_rect.h = sprite->getHeight();

	this->drawSprite(sprite->getTexture(), s_rect, s_rect);
}

void Viewport::draw() {
	SDL_RenderClear(this->renderer);
	this->drawScene();
#if RRE_DEBUGGING
	this->drawFPS();
#endif
	SDL_RenderPresent(this->renderer);
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

void Viewport::drawFPS() {
	// DEBUG:
	//~ this->logger->debug("FPS: " + to_string(this->current_fps));

	// TODO: optimize
	// FIXME: FontStore::buildTextSprite not working
	//~ Sprite* fps_sprite = FontStore::buildTextSprite(this->font_map, "FPS: "
			//~ + to_string(this->current_fps));
	//~ if (fps_sprite != nullptr) {
		//~ this->drawSprite(fps_sprite, 0, 0);
	//~ }

	SDL_Texture* texture = this->font_map->getTexture();

	int t_idx = 0;
	SDL_Rect t_rect = {9 * t_idx, 0, 9, 9};

	// F
	SDL_Rect s_rect = {5 * 9, 2 * 9, 9, 9};
	this->drawSprite(texture, s_rect, t_rect);
	t_idx++;
	t_rect.x = 9 * t_idx;
	// P
	s_rect.x = 9 * 2;
	s_rect.y = 9 * 3;
	this->drawSprite(texture, s_rect, t_rect);
	t_idx++;
	t_rect.x = 9 * t_idx;
	// S
	s_rect.x = 9 * 5;
	s_rect.y = 9 * 3;
	this->drawSprite(texture, s_rect, t_rect);
	t_idx++;
	t_rect.x = 9 * t_idx;
	// :
	s_rect.x = 9 * 2;
	s_rect.y = 9 * 0;
	this->drawSprite(texture, s_rect, t_rect);
	t_idx += 2;
	t_rect.x = 9 * t_idx;
	// ?
	s_rect.x = 9 * 5;
	s_rect.y = 9 * 0;
	this->drawSprite(texture, s_rect, t_rect);
	t_idx++;
	t_rect.x = 9 * t_idx;
	this->drawSprite(texture, s_rect, t_rect);
	t_idx++;
	t_rect.x = 9 * t_idx;
	this->drawSprite(texture, s_rect, t_rect);
	t_idx++;
	t_rect.x = 9 * t_idx;
}
