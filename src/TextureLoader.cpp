
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rwops.h>
#include <SDL2/SDL_surface.h>

#include "Logger.hpp"
#include "Path.hpp"
#include "SingletonRepo.hpp"
#include "TextureLoader.hpp"

using namespace std;


// FIXME: can't instantiate logger here
//~ namespace TextureLoader {
	//~ Logger logger = Logger::getLogger("TextureLoader");
//~ };

SDL_Texture* TextureLoader::absLoad(string apath) {
	// TODO: cache loaded textures
	Logger logger = Logger::getLogger("TextureLoader");

	SDL_Texture * texture = IMG_LoadTexture(GetViewport()->getRenderer(), apath.c_str());
	if (texture == nullptr) {
		logger.error("Failed to load texture: " + string(IMG_GetError()));
	} else {
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	}

	return texture;
}

SDL_Texture* TextureLoader::load(string rdpath) {
	// absolute path to image data file (only PNG supported)
	string apath = Path::rabs(Path::join("data", rdpath));
	if (!apath.ends_with(".png")) {
		apath += ".png";
	}

	return TextureLoader::absLoad(apath);
}

SDL_Texture* TextureLoader::loadFM(const uint8_t data[], const uint32_t data_size) {
	Logger logger = Logger::getLogger("TextureLoader");

	SDL_RWops* rw = SDL_RWFromMem((uint8_t*) data, data_size);
	if (rw == nullptr) {
		logger.error("Failed to load texture from memory: " + string(SDL_GetError()));
		return nullptr;
	}

	SDL_Surface* surface = IMG_Load_RW(rw, 1);
	if (surface == nullptr) {
		logger.error("Failed to load texture from memory: " + string(IMG_GetError()));
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(GetViewport()->getRenderer(), surface);
	SDL_FreeSurface(surface);
	if (texture == nullptr) {
		logger.error("Failed to load texture from memory: " + string(SDL_GetError()));
		return nullptr;
	}

	return texture;
}
