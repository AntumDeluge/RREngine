/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_IMAGE
#define RRE_IMAGE

#include <cstdint> // *int*_t

#include <SDL2/SDL_render.h>

#include "Logger.hpp"


/**
 * Base class to define images.
 */
class Image {
private:
	static Logger logger;

protected:
	/** Texture to draw with renderer. */
	SDL_Texture* texture;

	/** Full image width (in pixels). */
	int32_t width;
	/** Full image height (in pixels). */
	int32_t height;

	/**
	 * Sets texture used by this image.
	 *
	 * @param texture
	 *   Drawable texture.
	 */
	void setTexture(SDL_Texture* texture);

public:
	/** Default Constructor. */
	Image() {
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
	Image(SDL_Texture* texture);

	/**
	 * Default destructor.
	 */
	virtual ~Image() {
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
	int32_t getWidth() { return this->width; }

	/**
	 * Retrieves image height.
	 *
	 * @return
	 *   Image height in pixels.
	 */
	int32_t getHeight() { return this->height; }

	/**
	 * Checks if image is ready for rendering.
	 *
	 * @return
	 *   `true` if texture has been loaded.
	 */
	bool ready() {
		return this->texture != nullptr && width > 0 && height > 0;
	}
};

#endif /* RRE_IMAGE */
