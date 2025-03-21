/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "ImageImpl.hpp"


Logger ImageImpl::logger = Logger::getLogger("ImageImpl");

ImageImpl::ImageImpl(SDL_Texture* texture): ImageImpl() {
	setTexture(texture);
}


void ImageImpl::setTexture(SDL_Texture* texture) {
	if (texture == nullptr) {
		this->logger.warn("Image constructed with null texture");
		return;
	}
	this->texture = texture;
	// get dimensions
	SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
}
