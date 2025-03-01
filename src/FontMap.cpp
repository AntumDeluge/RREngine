/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>

#include "Dialog.h"
#include "FontMap.h"
#include "SingletonRepo.h"
#include "fileio.h"


// initialize static members
Logger* FontMap::logger = Logger::getLogger("FontMap");

FontMap::FontMap(SDL_Texture* texture, std::unordered_map<wchar_t, unsigned int> char_map,
		unsigned int w, unsigned int h) {
	this->texture = texture;
	this->char_map = char_map;
	this->w = w;
	this->h = h;
}

FontMap::FontMap(std::string file_path, std::unordered_map<wchar_t, unsigned int> char_map,
		unsigned int w, unsigned int h) {
	this->char_map = char_map;
	this->w = w;
	this->h = h;

	if (!fileExists(file_path)) {
		std::string msg = "Missing font map file: \"" + file_path + "\"";
		FontMap::logger->error(msg);
		Dialog::error(msg);
	} else {
		SDL_Surface* surface = IMG_Load(file_path.c_str());
		if (surface == nullptr) {
			std::string msg = "Failed to create surface from file: \"" + file_path + "\"";
			FontMap::logger->error(msg);
			Dialog::error(msg);
		} else {
			this->texture = SDL_CreateTextureFromSurface(GetViewport()->getRenderer(), surface);
			SDL_FreeSurface(surface);
		}
	}

	// DEBUG:
	//~ std::string msg = "New FontMap:\n";
	//~ for (std::pair<wchar_t, unsigned int> p : this->char_map) {
		//~ msg += "  " + std::to_string(p.first) + ((std::string) " => ") + std::to_string(p.second) + "\n";
	//~ }
	//~ Dialog::info("Debug", msg);
}
