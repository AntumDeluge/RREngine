/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FONT_MAP_H
#define RRE_FONT_MAP_H

#include <unordered_map>

#include <SDL2/SDL_render.h>

#include "ImageImpl.h"
#include "Logger.h"


/**
 * Class to handle drawing bitmap text.
 */
class FontMap: public ImageImpl {
private:
	static Logger logger;

	/** Pixel width of each character (excluding 2 pixels of padding). */
	uint32_t c_width;
	/** Pixel height of each character (excluding 2 pixels of padding). */
	uint32_t c_height;

	std::unordered_map<wchar_t, int> char_map;

public:
	/** default constructor. */
	FontMap() {
		this->c_width = 0;
		this->c_height = 0;
	}

	FontMap(SDL_Texture* texture, std::unordered_map<wchar_t, int> char_map, uint32_t c_width,
			uint32_t c_height);

	uint32_t getCharWidth() { return this->c_width; }
	uint32_t getCharHeight() { return this->c_height; }
	int getCharIndex(wchar_t c);
};

#endif /* RRE_FONT_MAP_H */
