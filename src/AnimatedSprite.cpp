/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "AnimatedSprite.hpp"

using namespace std;


Logger AnimatedSprite::logger = Logger::getLogger("AnimatedSprite");

// dummy animation to return in case animations have not been initialized
static Animation _dummy_mode = Animation();

AnimatedSprite::AnimatedSprite(SDL_Texture* texture): Sprite(texture) {
	// no animations have been defined yet
	current_mode = nullptr;
	default_mode = "dummy";
}

AnimatedSprite::AnimatedSprite(SDL_Texture* texture, uint32_t tile_width, uint32_t tile_height)
: Sprite(texture, tile_width, tile_height, 0) {
	// no animations have been defined yet
	current_mode = nullptr;
	default_mode = "dummy";
}

AnimatedSprite::AnimatedSprite(string id): Sprite(id) {
	// no animations have been defined yet
	current_mode = nullptr;
	default_mode = "dummy";
}

AnimatedSprite::AnimatedSprite(std::string id, uint32_t tile_width, uint32_t tile_height)
: Sprite(id, tile_width, tile_height, 0) {
	// no animations have been defined yet
	current_mode = nullptr;
	default_mode = "dummy";
}

void AnimatedSprite::setMode(string id) {
	if (modes.find(id) != modes.end()) {
		current_mode = &modes[id];
		return;
	}
	logger.warn("Unrecognized animation mode: " + id);
	current_mode = getDefaultMode();
}

Animation* AnimatedSprite::getDefaultMode() {
	if (modes.find(default_mode) != modes.end()) {
		return &modes[default_mode];
	}
	// return a dummy mode to prevent errors
	return &_dummy_mode;
}


void AnimatedSprite::render(ViewportRenderer* viewport, uint32_t x, uint32_t y, SDL_RendererFlip flags) {
	if (!ready()) {
		logger.warn("Animated sprite texture not ready");
		return;
	}

	uint32_t tile_index = current_mode->current();
	uint32_t cols = width / tile_width;
	uint32_t index_x = tile_index % cols;
	uint32_t index_y = tile_index / cols;

	viewport->drawImage(this,
			index_x*tile_width, index_y*tile_height, tile_width, tile_height, x, y, flags);
}
