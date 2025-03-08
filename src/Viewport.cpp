/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <iostream>
#include <string>

using namespace std;

#include "FontStore.h"
#include "GameConfig.h"
#include "SingletonRepo.h"
#include "TextureLoader.h"
#include "Viewport.h"
#include "reso.h"


// initialize singleton instance
Viewport* Viewport::instance = nullptr;

Viewport::Viewport() {
	this->logger = Logger::getLogger("Viewport");
	this->renderer = nullptr;
	// TODO: initial viewport font should be configured in game.xml
	this->font_map = nullptr; // cannot be set here because font maps have not yet loaded
	this->current_fps = 0;

	this->mode = GameMode::NONE;
	this->background = nullptr;
	this->fps_sprite = nullptr;
	this->scene = nullptr;
}

void Viewport::init(SDL_Window* window) {
	if (this->renderer != nullptr) {
		this->logger.warn("Viewport instance already initialized");
		return;
	}

#if RRE_DEBUGGING
	this->logger.debug("Creating Viewport renderer ...");
#endif

	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
	//~ SDL_SetRenderDrawColor(this->renderer, 0, 0, 20, SDL_ALPHA_OPAQUE);
}

void Viewport::shutdown() {
	this->unsetBackground();
	SDL_DestroyRenderer(this->renderer);
	this->renderer = nullptr;
	SDL_DestroyTexture(this->background);
	delete this->font_map;
	delete this->fps_sprite;
	this->unsetScene();
	for (Sprite* ts: this->text_sprites) {
		delete ts;
	}
	this->text_sprites.clear();
	delete Viewport::instance;
	Viewport::instance = nullptr;
}

void Viewport::setCurrentFPS(uint16_t fps) {
	this->current_fps = fps;
	this->fps_sprite = FontStore::buildTextSprite(this->font_map, "FPS: "
			+ to_string(this->current_fps));
}

void Viewport::setScale(uint16_t scale) {
	SDL_RenderSetScale(this->renderer, scale, scale);
}

void Viewport::unsetBackground() {
	if (this->background != nullptr) {
		SDL_DestroyTexture(this->background);
		this->background = nullptr;
	}
}

bool Viewport::setBackground(string rdpath) {
	this->unsetBackground();
	this->background = TextureLoader::load(rdpath);
	bool result = this->background != nullptr;
	if (!result) {
		string msg = "Failed to set background image";
		this->logger.error(msg);
	}
	return result;
}

void Viewport::unsetScene() {
	// clear any text from previous scene
	this->clearText();
	delete this->scene;
	this->scene = nullptr;
}

bool Viewport::setScene(Scene* scene) {
	this->scene = scene;
	bool result = this->scene != nullptr;
	if (!result) {
		this->logger.error("Failed to set scene");
	}
	return result;
}

void Viewport::setMode(GameMode::Mode mode) {
	if (mode == GameMode::TITLE) {
		this->setBackground(GameConfig::getBackground("title"));
		GetGameWindow()->playMusic(GameConfig::getMenuMusicId("title"));
	} else {
		this->unsetBackground();
		GetGameWindow()->stopMusic();
	}

	this->mode = mode;
}

void Viewport::drawTexture(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect) {
	if (texture == nullptr) {
		this->logger.error("Sprite drawing error; sprite undefined");
		return;
	}

	SDL_RenderCopy(this->renderer, texture, &s_rect, &t_rect);
}

void Viewport::drawImage(Sprite* sprite, uint32_t x, uint32_t y) {
	SDL_Rect s_rect;
	s_rect.x = 0;
	s_rect.y = 0;
	s_rect.w = sprite->getWidth();
	s_rect.h = sprite->getHeight();

	// target rectangle used for offset
	SDL_Rect t_rect; //= (SDL_Rect) {x, y, s_rect.w, s_rect.h};
	t_rect.x = x;
	t_rect.y = y;
	t_rect.w = s_rect.w;
	t_rect.h = s_rect.h;

	this->drawTexture(sprite->getTexture(), s_rect, t_rect);
}

void Viewport::draw() {
	SDL_RenderClear(this->renderer);
	// TODO: create Scene class that handles drawing tiles
	if (this->mode == GameMode::SCENE) {
		this->drawScene();
	} else if (this->mode == GameMode::TITLE) {
		this->drawTitle();
	}
	this->drawText();
	SDL_RenderPresent(this->renderer);
}

void Viewport::drawScene() {
	this->drawBackground();
	this->drawForeground();
	this->drawEntities();
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

void Viewport::drawTitle() {
	if (this->background == nullptr) {
		return;
	}

	int w, h;
	SDL_QueryTexture(this->background, NULL, NULL, &w, &h);

	this->drawTexture(this->background, (SDL_Rect) {0, 0, w, h},
			(SDL_Rect) {0, 0, RES1.first, RES1.second});
}

void Viewport::drawText() {
	for (int idx = 0; idx < this->text_sprites.size(); idx++) {
		// TODO:
		// - use text sprite class with x/y offsets predefined
		Sprite* sprite = this->text_sprites[idx];
		uint32_t center_x = (RES1.first / 2) - (sprite->getWidth() / 2);
		uint32_t center_y = (RES1.second / 2) + (sprite->getHeight() / 2);
		this->drawImage(sprite, center_x, center_y);
	}

#if RRE_DEBUGGING
	this->drawFPS();
#endif
}

void Viewport::addText(string text) {
	this->text_sprites.push_back(FontStore::buildTextSprite(this->font_map, text));
}

void Viewport::clearText() {
	for (int idx = 0; idx < this->text_sprites.size(); idx++) {
		delete this->text_sprites[idx];
	}
	this->text_sprites.clear();
}

void Viewport::drawFPS() {
#if RRE_DEBUGGING
	cout << "FPS: " << this->current_fps << "                \r";
#endif
	if (this->fps_sprite != nullptr) {
		this->drawImage(this->fps_sprite, 0, 0);
	}
}
