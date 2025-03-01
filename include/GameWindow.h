/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GAME_WINDOW_H
#define RRE_GAME_WINDOW_H

#include <iostream>
#include <string>

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_video.h>

#include "Logger.h"
#include "Viewport.h"


class GameWindow {
private:
	// singleton class
	static GameWindow* instance;
	GameWindow();
	~GameWindow() {}

	// delete copy constructor & assignment operator
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;

	/** Logger instance. */
	Logger* logger;
	SDL_Window* window;
	Viewport* viewport;
	/** Active music. */
	Mix_Music* music;

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

	void playMusic(std::string id);
	void stopMusic();
};

#endif /* RRE_GAME_WINDOW_H */
