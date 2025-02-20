/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <SDL2/SDL.h>

#include "frame.h"
#include "reso.h"

GameWindow::GameWindow() {

}

int GameWindow::init() {
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return 1;
	}

	// create the SDL frame
	SDL_Window* window = SDL_CreateWindow("Hello world!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RES1.first, RES1.second, SDL_WINDOW_SHOWN);

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

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
