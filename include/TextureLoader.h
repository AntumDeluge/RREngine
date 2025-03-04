
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_TEXTURE_LOADER
#define RRE_TEXTURE_LOADER

#include <string>

#include <SDL2/SDL_render.h>


/**
 * Namespace for loading PNG images into SDL textures.
 */
namespace TextureLoader {

	/**
	 * Loads image into SDL texture. Only supports PNG images.
	 *
	 * @param path
	 *   File path relative to data directory (excluding .png suffix).
	 * @return
	 *   Texture or `nullptr`.
	 */
	SDL_Texture* load(std::string path);
};

#endif /* RRE_TEXTURE_LOADER */
