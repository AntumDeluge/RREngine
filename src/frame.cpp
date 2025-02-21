/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <SDL2/SDL_mixer.h>

#include "frame.h"
#include "reso.h"

// initialize singleton instance
GameWindow* GameWindow::instance = nullptr;

GameWindow::GameWindow() {
	this->window = nullptr;
}

void GameWindow::setTitle(const std::string title) {
	SDL_SetWindowTitle(this->window, title.c_str());
}

int GameWindow::init(const std::string title, const int width, const int height) {
	// initialize video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), NULL);
		SDL_Quit();
		return 1;
	}

	// initialize audio subsystem
	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), NULL);
		SDL_Quit();
		return 1;
	}

	// initialize mixer for playing OGG audio files
	const int flags = MIX_INIT_OGG;
	const int initted = Mix_Init(flags);
	if (initted&flags != flags) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", Mix_GetError(), NULL);
		SDL_Quit();
		return 1;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", Mix_GetError(), NULL);
		Mix_Quit();
		SDL_Quit();
		return 1;
	}

	// create the SDL frame
	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height, SDL_WINDOW_SHOWN);

	// main loop flag
	bool quit = false;

	// event handler
	SDL_Event event;

	// TODO: move game loop to singleton class
	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	this->shutdown();

	return 0;
}

int GameWindow::init() {
	return this->init("R&R Engine", RES1.first, RES1.second);
}

void GameWindow::shutdown() {
	Mix_CloseAudio();
	Mix_Quit();
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}
