/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_IMAGE_IMPL
#define RRE_IMAGE_IMPL

#include <SDL2/SDL_render.h>

#include "Logger.hpp"


/**
 * Base class to define images.
 */
class ImageImpl {
private:
	static Logger logger;

protected:
	/** Texture to draw with renderer. */
	SDL_Texture* texture;

	/** Full image width (in pixels). */
	int width;
	/** Full image height (in pixels). */
	int height;

	/**
	 * Sets texture used by this image.
	 *
	 * @param texture
	 *   Drawable texture.
	 */
	void setTexture(SDL_Texture* texture);

public:
	/** Default Constructor. */
	ImageImpl() {
		this->texture = nullptr;
		this->width = 0;
		this->height = 0;
	}

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
	virtual ~ImageImpl() {
		if (texture != nullptr) {
			SDL_DestroyTexture(texture);
			texture = nullptr;
		}
	}

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

	/**
	 * Checks if image is ready for rendering.
	 *
	 * @return
	 *   `true` if texture has been loaded.
	 */
	bool ready() {
		return this->texture != nullptr;
	}
};

#endif /* RRE_IMAGE_IMPL */
