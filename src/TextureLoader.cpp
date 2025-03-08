
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

using namespace std;

#include <SDL2/SDL_image.h>

#include "Logger.h"
#include "Path.h"
#include "SingletonRepo.h"
#include "TextureLoader.h"


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
