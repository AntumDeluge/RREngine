/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FRAME_H
#define RRE_FRAME_H

#include <iostream>
#include <string>

#include <SDL2/SDL_video.h>

#include "viewport.h"


class GameWindow {
private:
	// singleton class
	static GameWindow* instance;
	GameWindow();
	~GameWindow() {}

	// delete copy constructor & assignment operator
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;

	SDL_Window* window;
	ViewPort* viewport;

public:
	static GameWindow* get() {
		if (instance == nullptr) {
			instance = new GameWindow();
		}
		return instance;
	}

	void setTitle(const std::string title);
	int init(const std::string title, const int width, const int height);
	// @deprecated
	int init();
	void shutdown();

	SDL_Window* getElement() {
		if (this->window == nullptr) {
			std::cout << "WARNING: returning SDL_Window before initialization" << std::endl;
		}
		return this->window;
	}
};

#endif /* RRE_FRAME_H */
