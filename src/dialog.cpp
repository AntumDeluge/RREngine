/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <iostream>

#include <SDL2/SDL.h>

#include "dialog.h"
#include "singletons.h"


void message(Uint32 flags, std::string title, std::string msg) {
	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		std::cerr << "ERROR: SDL video not initialized, cannot display dialog" << std::endl;
		std::cout << "(" << flags << ") " << title << ": " << msg << std::endl;
		return;
	}
	SDL_Window* window = GetGameWindow()->getElement();
	SDL_ShowSimpleMessageBox(flags, title.c_str(), msg.c_str(), window != nullptr ? window : NULL);
}

void Dialog::info(std::string title, std::string msg) {
	message(SDL_MESSAGEBOX_INFORMATION, title, msg);
}

void Dialog::warn(std::string msg) {
	message(SDL_MESSAGEBOX_WARNING, "Warning", msg);
}

void Dialog::error(std::string msg) {
	message(SDL_MESSAGEBOX_ERROR, "Error", msg);
}
