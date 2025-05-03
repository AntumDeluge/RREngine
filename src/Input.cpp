/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <algorithm>
// #include <cstdlib> // std::abs
#include <cstring>  // std::memcmp

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

Input::Input() {
	gamepad = nullptr;
	// TODO: move to `init` function
	updateGamepads();
}

bool Input::setGamepad(SDL_JoystickGUID guid) {
	if (gamepad != nullptr) {
		SDL_GameControllerClose(gamepad);
		gamepad = nullptr;
	}
	gamepad = getGamepad(guid);
	if (gamepad == nullptr) {
		SDL_SetError("device not found");
		return false;
	}
	SDL_JoystickGUID dev_guid = SDL_JoystickGetGUID(SDL_GameControllerGetJoystick(gamepad));
	if (memcmp(&dev_guid, &guid, sizeof(SDL_JoystickGUID)) != 0) {
		SDL_SetError("device GUID mismatch");
		return false;
	}
	return true;
}

bool Input::setGamepad(int32_t idx) {
	for (auto dev_info: gamepad_guids) {
		if (idx == dev_info.first) {
			return setGamepad(dev_info.second);
		}
	}
	return false;
}

SDL_GameController* Input::getGamepad(SDL_JoystickGUID guid) {
	for (int idx = 0; idx < SDL_NumJoysticks(); idx++) {
		SDL_JoystickGUID dev_guid = SDL_JoystickGetDeviceGUID(idx);
		if (memcmp(&dev_guid, &guid, sizeof(SDL_JoystickGUID)) == 0) {
			return SDL_GameControllerOpen(idx);
		}
	}
	return nullptr;
}

string Input::getGamepadName(SDL_GameController* dev) {
	return SDL_JoystickName(SDL_GameControllerGetJoystick(dev));
}

void Input::updateGamepads() {
	if (gamepad && !SDL_GameControllerGetAttached(gamepad)) {
		SDL_GameControllerClose(gamepad);
		gamepad = nullptr;
	}
	gamepad_guids.clear();
	for (int32_t dev_idx = 0; dev_idx < SDL_NumJoysticks(); dev_idx++) {
		SDL_JoystickGUID dev_guid = SDL_JoystickGetDeviceGUID(dev_idx);
		SDL_GameController* dev = getGamepad(dev_guid);
		if (!dev) {
			continue;
		}
		gamepad_guids.push_back({dev_idx, dev_guid});
		SDL_GameControllerClose(dev);
	}

#if RRE_DEBUGGING
	logger.debug("attached gamepads: ", to_string(gamepad_guids.size()));
	for (auto dev_info: gamepad_guids) {
		int32_t dev_idx = dev_info.first;
		SDL_JoystickGUID dev_guid = dev_info.second;
		SDL_GameController* dev = getGamepad(dev_guid);
		if (!dev) {
			continue;
		}
		SDL_Joystick* js = SDL_GameControllerGetJoystick(dev);
		char sguid[33];
		SDL_JoystickGetGUIDString(dev_guid, sguid, 33);
		logger.debug("- GUID:  ", sguid);
		logger.debug("  index: ", to_string(dev_idx));
		logger.debug("  name:  ", SDL_JoystickName(js));
		SDL_JoystickClose(js);
		SDL_GameControllerClose(dev);
	}
#endif
}

void Input::translateGamepadHatEvent(SDL_JoyHatEvent evt) {
	// TODO: allow to be customized
	if (evt.value == 0) {
		onKeyUp(SDLK_UP);
		onKeyUp(SDLK_DOWN);
		onKeyUp(SDLK_LEFT);
		onKeyUp(SDLK_RIGHT);
	}
	if (evt.value & 8) {
		onKeyDown(SDLK_LEFT);
	}
	if (evt.value & 2) {
		onKeyDown(SDLK_RIGHT);
	}
	if (evt.value & 1) {
		onKeyDown(SDLK_UP);
	}
	if (evt.value & 4) {
		onKeyDown(SDLK_DOWN);
	}
}

void Input::translateGamepadAxisEvent(SDL_JoyAxisEvent evt) {
	// FIXME: need to veto if sensitivity threshold not met

	// DEBUG:
	// logger.debug("axis ", to_string(evt.axis), " value: ", to_string(evt.value));

	// TODO:
}

void Input::translateGamepadButtonEvent(uint8_t button, uint8_t state) {
	// DEBUG:
	string msg = "";
	if (state == SDL_PRESSED) {
		msg = "pressed ";
	} else if (state == SDL_RELEASED) {
		msg = "released ";
	}
	msg += "button " + to_string(button);
	logger.debug(msg);

	// TODO:
}

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

void Input::onKeyDown(SDL_Keycode keycode) {
	if (this->keyIsPressed(keycode)) {
		return;
	}
	this->pressed_keys.push_back(keycode);

	if ((keycode == SDLK_RETURN || keycode == SDLK_KP_ENTER) && (keyIsPressed(SDLK_LALT)
			|| keyIsPressed(SDLK_RALT))) {
		GetGameWindow()->toggleFullscreen();
		GameLoop::setPaused(true, "KB_ALT_ENTER");
		// FIXME: key release simulation works but subsequent presses are still processed until actually released
		//releaseKey(keycode, KMOD_ALT);
		return;
	}
	// don't process game loop keyboard events while paused
	if (GameLoop::isPaused()) return;

	if (keyIsDirection(keycode)) {
		uint8_t new_dir = GetPlayerDirection();
		switch(keycode) {
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

void Input::onKeyUp(SDL_Keycode keycode) {
	if (!this->keyIsPressed(keycode)) {
		return;
	}
	this->pressed_keys.erase(remove(this->pressed_keys.begin(), this->pressed_keys.end(), keycode), this->pressed_keys.end());

	if ((keycode == SDLK_RETURN || keycode == SDLK_KP_ENTER)
			&& GameLoop::isPaused("KB_ALT_ENTER")) {
		GameLoop::setPaused(false);
		return;
	}
	// don't process game loop keyboard events while paused
	if (GameLoop::isPaused()) return;

	if (keyIsDirection(keycode)) {
		uint8_t new_dir = GetPlayerDirection();
		switch(keycode) {
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
