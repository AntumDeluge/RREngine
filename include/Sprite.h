/* Copyright © 2020 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SPRITE_H
#define RRE_SPRITE_H

#include <string>

#include <SDL2/SDL_render.h>

#include "ImageImpl.h"


/**
 * Sprite interface class.
 */
class Sprite: public ImageImpl {
public:
	Sprite(SDL_Texture* texture): ImageImpl(texture) {}
	Sprite(std::string id);
};

#endif /* RRE_SPRITE_H */
