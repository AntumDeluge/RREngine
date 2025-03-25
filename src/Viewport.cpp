/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <iostream>
#include <string>

#include "GameConfig.hpp"
#include "GameLoop.hpp"
#include "SingletonRepo.hpp"
#include "TextureLoader.hpp"
#include "Viewport.hpp"
#include "reso.hpp"
#include "store/FontMapStore.hpp"

using namespace std;


Logger Viewport::logger = Logger::getLogger("Viewport");

// initialize singleton instance
unique_ptr<Viewport> Viewport::instance = nullptr;
mutex Viewport::mtx;

Viewport::Viewport() {
	this->renderer = nullptr;
	// TODO: initial viewport font should be configured in game.xml
	this->font_map = nullptr; // cannot be set here because font maps have not yet loaded
	this->current_fps = 0;

	this->mode = GameMode::NONE;
	this->background = nullptr;
	this->fps_sprite = nullptr;
	this->movie = nullptr;
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
	delete this->movie;
	this->movie = nullptr;
}

void Viewport::setCurrentFPS(uint32_t fps) {
	this->current_fps = fps;
	this->fps_sprite = FontMapStore::buildTextSprite(this->font_map, "FPS: "
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

void Viewport::setMode(GameMode::Mode mode) {
	GetGameWindow()->stopMusic();
	this->clearText();
	this->unsetBackground();
	if (mode == GameMode::TITLE) {
		GetGameVisuals()->setScene("");
		this->setBackground(GameConfig::getBackground("title"));
		GetGameWindow()->playMusic(GameConfig::getMenuMusicId("title"));

		// DEBUG: placeholder of example for adding text to title screen
		this->addText("press enter");
	} else if (mode == GameMode::SCENE) {
		// DEBUG: placeholder example
		GetGameVisuals()->setScene("map1");
		this->addText("Sorry, nothing to do");
		this->addText("here yet. :(");
	} else if (mode == GameMode::INTRO) {
		this->movie = GameConfig::getIntro();
		this->movie->play();

#if RRE_DEBUGGING
		if (this->movie == nullptr) {
			this->logger.warn("No intro movie set");
		} else {
			this->logger.debug("Intro movie set");
		}
#endif
	}

	this->mode = mode;
}

void Viewport::drawTexture(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect, SDL_RendererFlip flags) {
	if (texture == nullptr) {
		this->logger.error("Sprite drawing error; sprite undefined");
		return;
	}

	//~ SDL_RenderCopy(this->renderer, texture, &s_rect, &t_rect);
	SDL_RenderCopyEx(this->renderer, texture, &s_rect, &t_rect, 0, nullptr, flags);
}

void Viewport::drawImage(Image* img, uint32_t sx, uint32_t sy, uint32_t s_width,
		uint32_t s_height, uint32_t x, uint32_t y, SDL_RendererFlip flags) {
	SDL_Rect s_rect;
	s_rect.x = sx;
	s_rect.y = sy;
	s_rect.w = s_width;
	s_rect.h = s_height;

	SDL_Rect t_rect;
	t_rect.x = x;
	t_rect.y = y;
	t_rect.w = s_rect.w;
	t_rect.h = s_rect.h;

	this->drawTexture(img->getTexture(), s_rect, t_rect, flags);
}

void Viewport::drawImage(Image* img, uint32_t x, uint32_t y, SDL_RendererFlip flags) {
	SDL_Rect s_rect;
	s_rect.x = 0;
	s_rect.y = 0;
	s_rect.w = img->getWidth();
	s_rect.h = img->getHeight();

	// target rectangle used for offset
	SDL_Rect t_rect; //= (SDL_Rect) {x, y, s_rect.w, s_rect.h};
	t_rect.x = x;
	t_rect.y = y;
	t_rect.w = s_rect.w;
	t_rect.h = s_rect.h;

	this->drawTexture(img->getTexture(), s_rect, t_rect, flags);
}

void Viewport::render() {
	SDL_RenderClear(this->renderer);
	// TODO: create Scene class that handles drawing tiles
	if (this->mode == GameMode::SCENE) {
		this->drawScene();
	} else if (this->mode == GameMode::TITLE) {
		this->drawTitle();
	} else if (this->mode == GameMode::INTRO) {
		if (this->movie == nullptr || this->movie->ended()) {
			GameLoop::setMode(GameMode::TITLE);
			return; // XXX: may be causing flicker between draws
		} else {
			this->movie->render(this);
		}
	}
	this->drawText();
	SDL_RenderPresent(this->renderer);
}

void Viewport::drawScene() {
	this->drawBackground();
	GetGameVisuals()->renderScene();
	this->drawForeground();
}

void Viewport::drawBackground() {
	// TODO:
}

void Viewport::drawForeground() {
	// TODO:
}

void Viewport::drawTitle() {
	if (this->background == nullptr) {
		return;
	}

	// FIXME: would it be better to store background as Image so we don't have to call `SDL_QueryTexture` every cycle?
	int w, h;
	SDL_QueryTexture(this->background, NULL, NULL, &w, &h);

	this->drawTexture(this->background, (SDL_Rect) {0, 0, w, h},
			(SDL_Rect) {0, 0, RES1.first, RES1.second});
}

void Viewport::drawText() {
	uint16_t y_offset = 0;
	for (Sprite* s: this->text_sprites) {
		uint16_t s_height = s->getHeight();
		// TODO: need sprite class that defines text position
		uint16_t center_x = (RES1.first / 2) - (s->getWidth() / 2);
		uint16_t center_y = (RES1.second / 2) - (s_height / 2);
		this->drawImage(s, center_x, center_y + y_offset);

		y_offset += s_height + 1;
	}

#if RRE_DEBUGGING
	this->drawFPS();
#endif
}

void Viewport::addText(string text) {
	this->text_sprites.push_back(FontMapStore::buildTextSprite(this->font_map, text));
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
