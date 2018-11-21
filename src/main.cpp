/* Copyright © 2018 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 *
 * WARNING: This software is in planning stages & is not ready
 * for regular use.
 */

#include <iostream>
#include <string>
using namespace std;

#include "config.h"

#include "frame.h"


const string ver = to_string(RREngine_VER_MAJ) + "." + to_string(RREngine_VER_MIN) + "." + to_string(RREngine_VER_REL); // @suppress("Invalid arguments") @suppress("Symbol is not resolved")

void showVersion();

int main(int argc, char** argv) {
	showVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "SDL initialization error: " << SDL_GetError() << endl;
		return 1;
	} else {
		cout << "SDL initialized" << endl;
	}

	SDL_Window* window = SDL_CreateWindow("Hello world!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RES1.first, RES1.second, SDL_WINDOW_SHOWN);

	// main loop flag
	bool quit = false;

	// event handler
	SDL_Event event;

	while (!quit) {
		pollIndex += 1;
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


void showVersion() {
	cout << "Version: " << ver << endl;
}
