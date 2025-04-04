
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


static Logger logger = Logger::getLogger("TextureLoader");

SDL_Texture* TextureLoader::absLoad(string apath) {
	// TODO: cache loaded textures

	SDL_Texture* texture = GetRenderer()->textureFromPath(apath);
	if (texture == nullptr) {
		logger.error("Failed to load texture: ", IMG_GetError());
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
	SDL_RWops* rw = SDL_RWFromMem((uint8_t*) data, data_size);
	if (rw == nullptr) {
		logger.error("Failed to load texture from memory: ", SDL_GetError());
		return nullptr;
	}

	SDL_Surface* surface = IMG_Load_RW(rw, 1);
	if (surface == nullptr) {
		logger.error("Failed to load texture from memory: ", IMG_GetError());
		return nullptr;
	}

	SDL_Texture* texture = GetRenderer()->textureFromSurface(surface);
	SDL_FreeSurface(surface);
	if (texture == nullptr) {
		logger.error("Failed to load texture from memory: ", SDL_GetError());
		return nullptr;
	}

	return texture;
}
