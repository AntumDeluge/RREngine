/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <algorithm>
#include <string>

#include "Input.hpp"

using namespace std;


Logger Input::logger = Logger::getLogger("Input");

// initialize singleton instance
unique_ptr<Input> Input::instance = nullptr;
mutex Input::mtx;

bool Input::keyIsPressed(SDL_Keycode key) {
	return find(this->pressed_keys.begin(), this->pressed_keys.end(), key) != this->pressed_keys.end();
}

bool Input::keyIsDirection(SDL_Keycode key) {
	return key == left || key == right || key == up || key == down;
}

void Input::onKeyDown(SDL_Keysym keysym) {
	if (this->keyIsPressed(keysym.sym)) {
		return;
	}
	this->pressed_keys.push_back(keysym.sym);

#ifdef RRE_DEBUGGING
	this->logger.debug("Key pressed: " + to_string(keysym.sym));
#endif
}

void Input::onKeyUp(SDL_Keysym keysym) {
	if (!this->keyIsPressed(keysym.sym)) {
		return;
	}
	this->pressed_keys.erase(remove(this->pressed_keys.begin(), this->pressed_keys.end(), keysym.sym), this->pressed_keys.end());

#ifdef RRE_DEBUGGING
	this->logger.debug("Key released: " + to_string(keysym.sym));
#endif
}
