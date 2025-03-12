/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_INPUT_H
#define RRE_INPUT_H

#include <vector>

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>

#include "Logger.h"


/**
 * Manages user input.
 */
class Input {
private:
	static Logger logger;

	/** List of keyboard keys currently depressed. */
	std::vector<SDL_Keycode> pressed_keys;

	/** Static singleton instance. */
	static Input* instance;

	/** Default constructor. */
	Input() {}

	/** Defaul destructor. */
	~Input() {
		if (Input::instance != nullptr) {
			delete Input::instance;
			Input::instance = nullptr;
		}
	}

	// delete copy constructor & assignment operator for singleton
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

	// default configuration (keyboard)
	SDL_KeyCode up = SDLK_UP;
	SDL_KeyCode down = SDLK_DOWN;
	SDL_KeyCode left = SDLK_LEFT;
	SDL_KeyCode right = SDLK_RIGHT;
	SDL_KeyCode fire = SDLK_a;
	SDL_KeyCode jump = SDLK_s;
	SDL_KeyCode cycle_w_next = SDLK_GREATER;
	SDL_KeyCode cycle_w_prev = SDLK_LESS;
	SDL_KeyCode menu = SDLK_ESCAPE;

	/**
	 * Checks if a key is depressed.
	 *
	 * @param key
	 *   Keycode to check.
	 * @return
	 *   `true` if found in pressed keys vector.
	 */
	bool keyIsPressed(SDL_Keycode key);

public:
	/**
	 * Initializes & retrieves singleton instance.
	 *
	 * @return
	 *   Static singleton instance.
	 */
	static Input* get() {
		if (instance == nullptr) {
			instance = new Input();
		}
		return instance;
	}

	/**
	 * Interprets keyboard key down events.
	 *
	 * @param key
	 *   Depressed key.
	 */
	void onKeyDown(SDL_Keysym key);

	/**
	 * Interprets keyboard key up events.
	 *
	 * @param key
	 *   Released key.
	 */
	void onKeyUp(SDL_Keysym key);
};

#endif /* RRE_INPUT_H */
