/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "FontMap.h"

using namespace std;


// initialize static members
Logger FontMap::logger = Logger::getLogger("FontMap");

FontMap::FontMap(SDL_Texture* texture, unordered_map<wchar_t, int> char_map, uint32_t c_width,
		uint32_t c_height): ImageImpl(texture) {
	this->char_map = char_map;
	this->c_width = c_width;
	this->c_height = c_height;
}

int FontMap::getCharIndex(wchar_t c) {
	if (this->char_map.find(c) != this->char_map.end()) {
		return this->char_map[c];
	}
	return -1;
}
