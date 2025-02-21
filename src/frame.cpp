/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "frame.h"
#include "reso.h"

GameWindow::GameWindow() {

// initialize singleton instance
GameWindow* GameWindow::instance = nullptr;

void GameWindow::setTitle(const std::string title) {
	SDL_SetWindowTitle(this->window, title.c_str());
}

int GameWindow::init(const int width, const int height) {
	// initialize video
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return 1;
	}

	// create the SDL frame
	this->window = SDL_CreateWindow("R&R Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	// main loop flag
	bool quit = false;

	// event handler
	SDL_Event event;

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
	return this->init(RES1.first, RES1.second);
}

void GameWindow::shutdown() {
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}
