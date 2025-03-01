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

using namespace std;


// initialize static members
Logger* FontMap::logger = Logger::getLogger("FontMap");

FontMap::FontMap(SDL_Texture* texture, unordered_map<wchar_t, int> char_map,
		unsigned int w, unsigned int h) {
	this->texture = texture;
	this->char_map = char_map;
	this->w = w;
	this->h = h;
}

FontMap::FontMap(string file_path, unordered_map<wchar_t, int> char_map,
		unsigned int w, unsigned int h) {
	this->char_map = char_map;
	this->w = w;
	this->h = h;

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
		}
	}

	// DEBUG:
	//~ string msg = "New FontMap:\n";
	//~ for (pair<wchar_t, int> p : this->char_map) {
		//~ msg += "  " + to_string(p.first) + ((string) " => ") + to_string(p.second) + "\n";
	//~ }
	//~ Dialog::info("Debug", msg);
}
