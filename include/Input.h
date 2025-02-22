/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

/** Configured input class. */

#ifndef RRE_INPUT_H
#define RRE_INPUT_H

#include <SDL2/SDL_keycode.h>


class Input {
private:
	// singleton class
	Input() {}
	~Input() {}
	static Input* instance;

	// delete copy constructor & assignment operator
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

public:
	static Input* get() {
		if (instance == nullptr) {
			instance = new Input();
		}
		return instance;
	}
};

#endif /* RRE_INPUT_H */
