/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "FontStore.h"
#include "Logger.h"
#include "SingletonRepo.h"

using namespace std;


// font map cache
unordered_map<string, FontMap*> fmap_cache = {};

void FontStore::addMap(string fid, FontMap* fmap) {
	if (fmap_cache.find(fid) != fmap_cache.end()) {
		Logger::getLogger("FontStore")->warn("Overwriting font map with id \"" + fid + "\"");
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
	Logger* logger = Logger::getLogger("FontStore");

	// TODO: cache text sprites for redraw (probably in Viewport class)

	if (fmap == nullptr) {
		logger->error("Undefined font map");
		return nullptr;
	}

	// get character dimensions
	uint32_t c_width = fmap->getCharWidth(); // + 1;
	uint32_t c_height = fmap->getCharHeight(); // + 1;

	// number of characters to be drawn
	uint16_t c_count = text.length();

	// dimensions of entire text image & compensate for padding
	uint32_t full_width = c_count * (c_width + 1);

	// source image
	SDL_Texture* s_texture = fmap->getTexture();

	SDL_Renderer* renderer = GetViewport()->getRenderer();

	SDL_Texture* t_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_TARGET, 9, 9);
			//~ SDL_TEXTUREACCESS_TARGET, full_width, c_height + 1);
	if (t_texture == nullptr) {
		logger->error((string) "Cannot build text sprite: " + SDL_GetError());
		return nullptr;
	}

	// set render target to background
	SDL_SetRenderTarget(renderer, t_texture);

	SDL_RenderClear(renderer);

	//~ SDL_Rect t_rect;
	//~ t_rect.x = 0;
	//~ t_rect.y = 0;
	//~ t_rect.w = c_width + 1;
	//~ t_rect.h = c_height + 1;

	// full width of source image
	uint32_t s_width = fmap->getWidth();

	// number of columns in source image
	uint16_t ix = s_width / (c_width + 2);

	//~ for (int idx = 0; idx < c_count; idx++) {
		//~ wchar_t c = text[idx];
		//~ int c_index = fmap->getCharIndex(c);
		//~ if (c_index < 0) {
			//~ logger->error("Unsupported font map character: \"" + string(1, c) + "\"");
			//~ c_index = 0;
		//~ }

		//~ SDL_Rect s_rect;
		//~ s_rect.x = c_index * (c_width + 2);
		//~ s_rect.y = c_index / ix * (c_height + 2);
		//~ s_rect.w = c_width + 1;
		//~ s_rect.h = c_height + 1;

		//~ t_rect.x = idx * c_width + 1;

		//~ SDL_RenderCopy(renderer, s_texture, &s_rect, &t_rect);
	//~ }

	// DEBUG:
	SDL_Rect s_rect = { 1, 1, 9, 9 };
	SDL_Rect t_rect = { 0, 0, 9, 9 };
	SDL_RenderCopy(renderer, s_texture, &s_rect, &t_rect);

	// restore render target to screen
	SDL_SetRenderTarget(renderer, nullptr);

	//~ int t_width, t_height;
	//~ SDL_QueryTexture(t_texture, nullptr, nullptr, &t_width, &t_height);
	//~ if (t_width != full_width || t_height != c_height + 1) {
		//~ logger->warn("Expected sprite dimensions of " + to_string(full_width) + "x"
				//~ + to_string(c_height + 1) + " but got " + to_string(t_width) + "x" + to_string(t_height));
	//~ }

	//~ return new Sprite(t_texture, t_width, t_height);

	// DEBUG:
	return new Sprite(t_texture, 9, 9);
}
