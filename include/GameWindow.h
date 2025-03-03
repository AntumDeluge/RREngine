/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GAME_WINDOW_H
#define RRE_GAME_WINDOW_H

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

	std::string title;
	SDL_Window* window;
	Viewport* viewport;
	/** Active music. */
	Mix_Music* music;
	/** Game loop iterator. */
	bool quit;

public:
	static GameWindow* get() {
		if (instance == nullptr) {
			instance = new GameWindow();
		}
		return instance;
	}

	void setTitle(const std::string title);
	int init(const std::string title, const int width, const int height);
	int init(const int width, const int height) {
		return this->init(this->title, width, height);
	}
	/** Sets game loop to be ended & shutdown cleanly. */
	void endGameLoop();
	void shutdown();

	SDL_Window* getElement() {
		if (this->window == nullptr) {
			this->logger->warn("Returning SDL_Window before initialization");
		}
		return this->window;
	}

	Viewport* getViewport() { return this->viewport; }

	void playMusic(std::string id);
	void stopMusic();
};

#endif /* RRE_GAME_WINDOW_H */
