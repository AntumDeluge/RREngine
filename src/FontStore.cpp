/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

using namespace std;

#include "FontStore.h"
#include "Logger.h"
#include "SingletonRepo.h"


// font map cache
unordered_map<string, FontMap*> fmap_cache = {};

void FontStore::addMap(string fid, FontMap* fmap) {
	if (fmap_cache.find(fid) != fmap_cache.end()) {
		Logger::getLogger("FontStore").warn("Overwriting font map with id \"" + fid + "\"");
	}
	fmap_cache[fid] = fmap;
}

FontMap* FontStore::getMap(string fid) {
	if (fmap_cache.find(fid) != fmap_cache.end()) {
		return fmap_cache[fid];
	}
	return nullptr;
}

Sprite* FontStore::buildTextSprite(FontMap* fmap, string text) {
	Logger logger = Logger::getLogger("FontStore");

	// TODO: cache text sprites for redraw (probably in Viewport class)

	if (fmap == nullptr) {
		logger.error("Undefined font map");
		return nullptr;
	}

	// get character dimensions
	uint32_t c_width = fmap->getCharWidth();
	uint32_t c_height = fmap->getCharHeight();

	// number of characters to be drawn
	uint16_t c_count = text.length();

	// dimensions of entire text image & compensate for padding
	uint32_t full_width = c_count * c_width;

	// source image
	SDL_Texture* s_texture = fmap->getTexture();

	SDL_Renderer* renderer = GetViewport()->getRenderer();

	SDL_Texture* t_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_TARGET, full_width, c_height);
	if (t_texture == nullptr) {
		logger.error((string) "Cannot build text sprite: " + SDL_GetError());
		return nullptr;
	}

	// set render target to background
	SDL_SetRenderTarget(renderer, t_texture);

	SDL_RenderClear(renderer);

	SDL_Rect t_rect;
	t_rect.x = 0;
	t_rect.y = 0;
	t_rect.w = c_width;
	t_rect.h = c_height;

	// full width of source image
	uint32_t s_width = fmap->getWidth();

	// number of columns in source image
	uint16_t ix = s_width / c_width;

	for (int idx = 0; idx < c_count; idx++) {
		wchar_t c = text[idx];
		if (c == ' ') {
			// don't draw anything for whitespace
			continue;
		}
		int c_index = fmap->getCharIndex(c);
		if (c_index < 0) {
			logger.error("Unsupported font map character: \"" + string(1, c) + "\""); // @suppress("Symbol is not resolved")
			c_index = 0;
		}

		uint16_t x_offset = c_index % ix;
		uint16_t y_offset = c_index / ix;

		SDL_Rect s_rect;
		s_rect.x = x_offset * c_width;
		s_rect.y = y_offset * c_height;
		s_rect.w = c_width;
		s_rect.h = c_height;

		t_rect.x = idx * c_width;

		SDL_RenderCopy(renderer, s_texture, &s_rect, &t_rect);
	}

	// restore render target to screen
	SDL_SetRenderTarget(renderer, nullptr);

	int t_width, t_height;
	SDL_QueryTexture(t_texture, nullptr, nullptr, &t_width, &t_height);
	if (t_width != full_width || t_height != c_height) {
		logger.warn("Expected sprite dimensions of " + to_string(full_width) + "x"
				+ to_string(c_height) + " but got " + to_string(t_width) + "x" + to_string(t_height));
	}

	return new Sprite(t_texture);
}
