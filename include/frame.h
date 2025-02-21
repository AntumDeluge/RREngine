/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FRAME_H
#define RRE_FRAME_H

#include <SDL2/SDL.h>
#include <string>


class GameWindow {
private:
	// singleton class
	static GameWindow* instance;
	GameWindow() {}
	~GameWindow() {}

	// delete copy & assignment operator
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;

	SDL_Window* window;

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
};

#endif /* RRE_FRAME_H */
