/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "ImageImpl.h"


ImageImpl::ImageImpl(SDL_Texture* texture) {
	this->texture = texture;
	// get dimensions
	SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
}
