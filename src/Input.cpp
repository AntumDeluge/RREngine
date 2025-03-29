/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <algorithm>
#include <string>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include "GameLoop.hpp"
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

void Input::releaseKey(SDL_Keycode key, uint16_t mod) {
	SDL_KeyboardEvent event;
	event.type = SDL_KEYUP;
	event.timestamp = SDL_GetTicks64();
	event.windowID = SDL_GetWindowID(GetGameWindow()->getElement());
	event.state = SDL_RELEASED;
	event.keysym.sym = key;
	event.keysym.mod = mod;
	event.keysym.scancode = SDL_GetScancodeFromKey(key);

	SDL_PushEvent((SDL_Event*) &event);
}

void Input::onKeyDown(SDL_Keysym keysym) {
	if (this->keyIsPressed(keysym.sym)) {
		return;
	}
	this->pressed_keys.push_back(keysym.sym);

	if ((keysym.sym == SDLK_RETURN || keysym.sym == SDLK_KP_ENTER) && (keyIsPressed(SDLK_LALT)
			|| keyIsPressed(SDLK_RALT))) {
		GetGameWindow()->toggleFullscreen();
		GameLoop::setPaused(true, "KB_ALT_ENTER");
		// FIXME: key release simulation works but subsequent presses are still processed until actually released
		//releaseKey(keysym.sym, KMOD_ALT);
		return;
	}
	// don't process game loop keyboard events while paused
	if (GameLoop::isPaused()) return;

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

	if ((keysym.sym == SDLK_RETURN || keysym.sym == SDLK_KP_ENTER)
			&& GameLoop::isPaused("KB_ALT_ENTER")) {
		GameLoop::setPaused(false);
		return;
	}
	// don't process game loop keyboard events while paused
	if (GameLoop::isPaused()) return;

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
