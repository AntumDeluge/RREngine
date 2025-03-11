/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "AnimatedSprite.h"

using namespace std;


Logger AnimatedSprite::logger = Logger::getLogger("AnimatedSprite");

AnimatedSprite::AnimatedSprite(SDL_Texture* texture): Sprite(texture) {
	// create dummy mode
	this->default_mode = "dummy";
	this->addMode(this->default_mode, true, {});
	this->setMode(this->default_mode);
}

AnimatedSprite::AnimatedSprite(std::string id): Sprite(id) {
	// create dummy mode
	this->default_mode = "dummy";
	this->addMode(this->default_mode, true, {});
	this->setMode(this->default_mode);
}

AnimatedSprite::AnimatedSprite(): AnimatedSprite(nullptr) {}

void AnimatedSprite::addMode(string id, bool loop, Animation* animation) {
	this->modes[id] = new AnimationMode;
	this->modes[id]->first = loop;
	this->modes[id]->second = animation;
}

void AnimatedSprite::setMode(string id) {
	if (this->modes.find(id) != this->modes.end()) {
		this->current_mode = this->modes[id];
		return;
	}

	this->logger.warn("Unrecognized animation mode: " + id);
	this->current_mode = this->getDefaultMode();
}

AnimationMode* AnimatedSprite::getDefaultMode() {
	if (this->modes.find(this->default_mode) != this->modes.end()) {
		return this->modes[this->default_mode];
	}

	// dummy mode
	AnimationMode* dummy;
	dummy->first = true;
	dummy->second = new Animation;
	return dummy;
}


void AnimatedSprite::render(ViewportRenderer* viewport, uint16_t x, uint16_t y) {
	// TODO:
}
