/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_IMAGE_IMPL
#define RRE_IMAGE_IMPL

#include <SDL2/SDL_render.h>


/**
 * Base class to define images.
 */
class ImageImpl {
private:
	/** Texture to draw with renderer. */
	SDL_Texture* texture;

	/** Full image width (in pixels). */
	int width;
	/** Full image height (in pixels). */
	int height;

public:
	/**
	 * Image definition constructor.
	 *
	 * @param texture
	 *   Texture to draw with renderer.
	 */
	ImageImpl(SDL_Texture* texture);

	/**
	 * Default destructor.
	 */
	~ImageImpl() { SDL_DestroyTexture(this->texture); }

	/**
	 * Retrieves drawable texture.
	 *
	 * @return
	 *   `SDL_Texture` instance.
	 */
	SDL_Texture* getTexture() { return this->texture; }

	/**
	 * Retrieves image width.
	 *
	 * @return
	 *   Image width in pixels.
	 */
	int getWidth() { return this->width; }

	/**
	 * Retrieves image height.
	 *
	 * @return
	 *   Image height in pixels.
	 */
	int getHeight() { return this->height; }
};

#endif /* RRE_IMAGE_IMPL */
