
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_TEXTURE
#define RRE_TEXTURE

#include <string>

#include <SDL2/SDL_render.h>


namespace Texture {

	SDL_Texture* getTexture(std::string path);
};

#endif /* RRE_TEXTURE */
