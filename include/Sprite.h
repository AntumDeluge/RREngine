/* Copyright © 2020 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SPRITE_H
#define RRE_SPRITE_H

#include <cstdint>
#include <string>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include "ImageImpl.h"


/**
 * Sprite interface class.
 */
class Sprite: public ImageImpl {
private:
	uint32_t expires = 0;

public:
	Sprite(SDL_Texture* texture): ImageImpl(texture) {}
	Sprite(std::string id);

	void setExpiration(uint32_t expires) {
		this->expires = expires;
	}

	bool expired() {
		return this->expires != 0 && SDL_GetTicks64() >= this->expires;
	}
};

#endif /* RRE_SPRITE_H */
