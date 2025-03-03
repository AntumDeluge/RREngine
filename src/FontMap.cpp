/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>

#include "Dialog.h"
#include "Filesystem.h"
#include "FontMap.h"
#include "SingletonRepo.h"

using namespace std;


// initialize static members
Logger* FontMap::logger = Logger::getLogger("FontMap");

FontMap::FontMap(SDL_Texture* texture, unordered_map<wchar_t, int> char_map, uint32_t c_width,
		uint32_t c_height) {
	this->texture = texture;
	this->char_map = char_map;
	this->c_width = c_width;
	this->c_height = c_height;

	int width, height;
	SDL_QueryTexture(this->texture, nullptr, nullptr, &width, &height);
	this->w = width;
	this->h = height;
}

FontMap::FontMap(string file_path, unordered_map<wchar_t, int> char_map, uint32_t c_width,
		uint32_t c_height) {
	this->char_map = char_map;
	this->c_width = c_width;
	this->c_height = c_height;

	this->w = 0;
	this->h = 0;

	if (!fileExists(file_path)) {
		string msg = "Missing font map file: \"" + file_path + "\"";
		FontMap::logger->error(msg);
		Dialog::error(msg);
	} else {
		SDL_Surface* surface = IMG_Load(file_path.c_str());
		if (surface == nullptr) {
			string msg = "Failed to create surface from file: \"" + file_path + "\"";
			FontMap::logger->error(msg);
			Dialog::error(msg);
		} else {
			this->texture = SDL_CreateTextureFromSurface(GetViewport()->getRenderer(), surface);
			SDL_FreeSurface(surface);

			int width, height;
			SDL_QueryTexture(this->texture, nullptr, nullptr, &width, &height);
			this->w = width;
			this->h = height;
		}
	}

	// DEBUG:
	//~ string msg = "New FontMap:\n";
	//~ for (pair<wchar_t, int> p : this->char_map) {
		//~ msg += "  " + string(1, p.first) + ((string) " => ") + to_string(p.second) + "\n";
	//~ }
	//~ Dialog::info("Debug", msg);
}

int FontMap::getCharIndex(wchar_t c) {
	if (this->char_map.find(c) != this->char_map.end()) {
		return this->char_map[c];
	}
	return -1;
}
