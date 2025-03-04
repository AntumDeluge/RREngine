
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

using namespace std;

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>

#include "Logger.h"
#include "Path.h"
#include "SingletonRepo.h"
#include "TextureLoader.h"


// FIXME: can't instantiate logger here
//~ namespace TextureLoader {
	//~ Logger* logger = Logger::getLogger("TextureLoader");
//~ };

SDL_Texture* TextureLoader::load(string rdpath) {
	// TODO: cache loaded textures
	Logger* logger = Logger::getLogger("TextureLoader");

	// absolute path to image data file (only PNG supported)
	const string adpath = Path::rabs(Path::join("data", rdpath)) + ".png";
	SDL_Surface* surface = IMG_Load(adpath.c_str());
	if (surface == nullptr) {
		logger->error("Failed to load image surface: \"" + adpath + "\"");
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(GetViewport()->getRenderer(), surface);
	SDL_FreeSurface(surface);

	if (texture == nullptr) {
		logger->error("Failed to create texture from surface: \"" + adpath + "\"");
	}

	return texture;
}
