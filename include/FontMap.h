/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FONT_MAP_H
#define RRE_FONT_MAP_H

#include <unordered_map>

#include <SDL2/SDL_render.h>

#include "Logger.h"


/**
 * Class to handle drawing bitmap text.
 *
 * FIXME:
 * - use signed int for -1 to represent char not supported
 */
class FontMap {
private:
	static Logger* logger;

	SDL_Texture* texture;
	std::unordered_map<wchar_t, int> char_map;
	/** Pixel width of each character (excluding 2 pixels of padding). */
	unsigned int w;
	/** Pixel height of each character (excluding 2 pixels of padding). */
	unsigned int h;

public:
	FontMap(SDL_Texture* texture, std::unordered_map<wchar_t, int> char_map,
			unsigned int w, unsigned int h);

	FontMap(std::string file_path, std::unordered_map<wchar_t, int> char_map,
			unsigned int w, unsigned int h);

	SDL_Texture* getTexture() {
		return this->texture;
	}
};

#endif /* RRE_FONT_MAP_H */
