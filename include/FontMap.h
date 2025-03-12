/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FONT_MAP_H
#define RRE_FONT_MAP_H

#include <cstdint> // *int*_t
#include <unordered_map>

#include <SDL2/SDL_render.h>

#include "ImageImpl.h"
#include "Logger.h"


/**
 * Class to handle drawing bitmap text.
 *
 * Only monospace text is supported.
 *
 * TODO: rename file to FontMap.hpp
 */
class FontMap: public ImageImpl {
private:
	static Logger logger;

	/** Pixel width of each character (excluding 2 pixels of padding). */
	uint32_t c_width;
	/** Pixel height of each character (excluding 2 pixels of padding). */
	uint32_t c_height;

	/** Mapping of texture tile indexes. */
	std::unordered_map<wchar_t, int32_t> char_map;

public:
	/** Default constructor. */
	FontMap() {
		this->c_width = 0;
		this->c_height = 0;
	}

	/**
	 * Creates a font map.
	 *
	 * @param texture
	 *   Image texture used for drawing characters on renderer.
	 * @param char_map
	 *   Mapping of texture tile indexes.
	 * @param c_width
	 *   Pixel width of each character.
	 * @param c_height
	 *   Pixel height of each character.
	 */
	FontMap(SDL_Texture* texture, std::unordered_map<wchar_t, int> char_map, uint32_t c_width,
			uint32_t c_height);

	/**
	 * Retrieves character width.
	 *
	 * @return
	 *   Pixel width of each character.
	 */
	uint32_t getCharWidth() { return this->c_width; }

	/**
	 * Retrieves character height.
	 *
	 * @return
	 *   Pixel height of each character.
	 */
	uint32_t getCharHeight() { return this->c_height; }

	/**
	 * Retrieves index of a given character.
	 *
	 * @param c
	 *   Character that is to be drawn.
	 * @return
	 *   Texture index of character or -1 if not mapped.
	 */
	int32_t getCharIndex(wchar_t c);
};

#endif /* RRE_FONT_MAP_H */
