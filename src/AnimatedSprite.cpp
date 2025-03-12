/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "AnimatedSprite.hpp"

using namespace std;


Logger AnimatedSprite::logger = Logger::getLogger("AnimatedSprite");

// dummy animation to return in case animations have not been initialized
const static Animation _dummy_mode = Animation();

AnimatedSprite::AnimatedSprite(SDL_Texture* texture): Sprite(texture) {
	// no animations have been defined yet
	current_mode = nullptr;
	default_mode = "dummy";
}

AnimatedSprite::AnimatedSprite(string id): Sprite(id) {
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

const Animation* AnimatedSprite::getDefaultMode() {
	if (modes.find(default_mode) != modes.end()) {
		return &modes[default_mode];
	}
	// return a dummy mode to prevent errors
	return &_dummy_mode;
}


void AnimatedSprite::render(ViewportRenderer* viewport, uint16_t x, uint16_t y) {
	// TODO:
}
