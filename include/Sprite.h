/* Copyright © 2020 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SPRITE_H
#define RRE_SPRITE_H

#include <cstdint> // uint32_t
#include <string>

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "Logger.h"


/**
 * Sprite interface class.
 *
 * TODO: should be subclass of ImageImpl
 */
class Sprite {
private:
	/** Static logger instance. */
	// FIXME: can't make logger static?
	//~ static Logger* logger;
	Logger* logger;

	SDL_Texture* texture;
	uint32_t w;
	uint32_t h;

public:
	Sprite(std::string id);
	Sprite(SDL_Texture* texture, uint32_t w, uint32_t h);
	~Sprite() {
		SDL_DestroyTexture(this->texture);
	}

	SDL_Texture* getTexture() { return this->texture; }
	uint32_t getWidth() { return this->w; }
	uint32_t getHeight() { return this->h; }
};


#endif /* RRE_SPRITE_H */
