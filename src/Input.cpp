/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <algorithm>
#include <string>

#include "GlobalFunctions.hpp"
#include "Input.hpp"
#include "SingletonRepo.hpp"
#include "enum/MomentumDir.hpp"

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

	if (keysym.sym == SDLK_RETURN && (keyIsPressed(SDLK_LALT) || keyIsPressed(SDLK_RALT))) {
		GetGameWindow()->toggleFullscreen();
	}

	if (keyIsDirection(keysym.sym)) {
		uint8_t new_dir = GetPlayerDirection();
		switch(keysym.sym) {
			case SDLK_LEFT:
				new_dir = AddPlayerDirection(MomentumDir::LEFT);
				break;
			case SDLK_RIGHT:
				new_dir = AddPlayerDirection(MomentumDir::RIGHT);
				break;
			case SDLK_UP:
				new_dir = AddPlayerDirection(MomentumDir::UP);
				break;
			case SDLK_DOWN:
				new_dir = AddPlayerDirection(MomentumDir::DOWN);
				break;
		}

#ifdef RRE_DEBUGGING
		logger.debug("Player direction: ", to_string(new_dir));
#endif
	}
}

void Input::onKeyUp(SDL_Keysym keysym) {
	if (!this->keyIsPressed(keysym.sym)) {
		return;
	}
	this->pressed_keys.erase(remove(this->pressed_keys.begin(), this->pressed_keys.end(), keysym.sym), this->pressed_keys.end());

	if (keyIsDirection(keysym.sym)) {
		uint8_t new_dir = GetPlayerDirection();
		switch(keysym.sym) {
			case SDLK_LEFT:
				new_dir = RemovePlayerDirection(MomentumDir::LEFT);
				break;
			case SDLK_RIGHT:
				new_dir = RemovePlayerDirection(MomentumDir::RIGHT);
				break;
			case SDLK_UP:
				new_dir = RemovePlayerDirection(MomentumDir::UP);
				break;
			case SDLK_DOWN:
				new_dir = RemovePlayerDirection(MomentumDir::DOWN);
				break;
		}

#ifdef RRE_DEBUGGING
		logger.debug("Player direction: ", to_string(new_dir));
#endif
	}
}
