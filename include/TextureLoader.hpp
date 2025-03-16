
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_TEXTURE_LOADER
#define RRE_TEXTURE_LOADER

#include <cstdint> // uint*_t
#include <string>

#include <SDL2/SDL_render.h>


/**
 * Namespace for loading PNG images into SDL textures.
 *
 * FIXME: need failsafes in case renderer not initialized (E.g. trying to get a texture within Viewport constructor)
 */
namespace TextureLoader {

	/**
	 * Loads image into SDL texture.
	 *
	 * @param apath
	 *   Absolute path to image resource.
	 * @return
	 *   Texture or `nullptr`.
	 */
	SDL_Texture* absLoad(std::string apath);

	/**
	 * Loads image into SDL texture. Only supports PNG images.
	 *
	 * @param rdpath
	 *   File path relative to data directory (.png suffix optional).
	 * @return
	 *   Texture or `nullptr`.
	 */
	SDL_Texture* load(std::string rdpath);

	/**
	 * Loads image data into SDL texture.
	 *
	 * @param data
	 *   PNG image data.
	 * @return
	 *   Texture.
	 */
	SDL_Texture* loadFM(const uint8_t data[], const uint32_t data_size);
};

#endif /* RRE_TEXTURE_LOADER */
