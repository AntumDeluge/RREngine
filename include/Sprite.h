/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SPRITE_H
#define RRE_SPRITE_H

#include <cstdint> // uint*_t
#include <string>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include "ImageImpl.h"
#include "Logger.h"
#include "ViewportRenderer.h"


/**
 * Sprite interface class.
 */
class Sprite: public ImageImpl {
private:
	static Logger logger;

	uint32_t expires = 0;

public:
	Sprite(SDL_Texture* texture): ImageImpl(texture) {}
	Sprite(std::string id);
	Sprite(): Sprite(nullptr) {}

	void setExpiration(uint32_t expires) {
		this->expires = expires;
	}

	bool expired() {
		return this->expires != 0 && SDL_GetTicks64() >= this->expires;
	}
};

#endif /* RRE_SPRITE_H */
