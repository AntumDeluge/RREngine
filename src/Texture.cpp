
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

using namespace std;

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>

#include "Logger.h"
#include "SingletonRepo.h"
#include "Texture.h"


// FIXME: can't instantiate logger here
//~ namespace Texture {
	//~ Logger* logger = Logger::getLogger("Texture");
//~ };

SDL_Texture* Texture::getTexture(string path) {
	// TODO: cache loaded textures
	Logger* logger = Logger::getLogger("Texture");

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr) {
		logger->error("Failed to load image surface: \"" + path + "\"");
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(GetViewport()->getRenderer(), surface);
	SDL_FreeSurface(surface);

	if (texture == nullptr) {
		logger->error("Failed to create texture from surface: \"" + path + "\"");
	}

	return texture;
}
