/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <SDL2/SDL.h> // SDL2 defines SDL_Init in main header, this has been moved to SDL_init.h in SDL3
#include <SDL2/SDL_image.h>

#include "AudioStore.h"
#include "Dialog.h"
#include "FontMapLoader.h"
#include "FontStore.h"
#include "GameWindow.h"
#include "SingletonRepo.h"

using namespace std;


// initialize singleton instance
GameWindow* GameWindow::instance = nullptr;

GameWindow::GameWindow() {
	this->logger = Logger::getLogger("GameWindow");
	this->title = "R&R Engine";
	this->window = nullptr;
	this->viewport = nullptr;
	this->music = nullptr;
	this->quit = false;
}

void GameWindow::setTitle(const string title) {
	this->title = title;
	if (this->window != nullptr) {
		SDL_SetWindowTitle(this->window, this->title.c_str());
	}
}

int GameWindow::init(const string title, const int width, const int height) {
	this->logger.debug("Initializing SDL ...");

	this->title = title;

	// initialize video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		// NOTE: message logged to console as video subsystem failed to initialize
		string msg = SDL_GetError();
		this->logger.error(msg);
		Dialog::error(msg);
		SDL_Quit();
		return 1;
	}

	// create the SDL frame & viewport renderer
	this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	this->viewport = GetViewport();
	this->viewport->init(this->window);

	// initialize PNG image support
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		string msg = IMG_GetError();
		this->logger.error(msg);
		Dialog::error(msg);
		this->shutdown();
		return 1;
	}

	// initialize audio subsystem
	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		string msg = SDL_GetError();
		this->logger.error(msg);
		Dialog::error(msg);
		this->shutdown();
		return 1;
	}

	// initialize mixer for playing OGG audio files
	const int flags = MIX_INIT_OGG;
	const int initted = Mix_Init(flags);
	if (initted&flags != flags) {
		string msg = Mix_GetError();
		this->logger.error(msg);
		Dialog::error(msg);
		this->shutdown();
		return 1;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
		string msg = Mix_GetError();
		this->logger.error(msg);
		Dialog::error(msg);
		this->shutdown();
		return 1;
	}

	// FIXME: move to `DataLoader` class startup?
	FontMapLoader::loadConfig();
	this->viewport->setFontMap(FontStore::getMap("main"));

	return 0;
}

void GameWindow::endGameLoop() {
	this->quit = true;
}

void GameWindow::playMusic(string id) {
	if (Mix_PlayingMusic() != 0) {
		// close previous stream
		this->stopMusic();
	}

	string file_music = AudioStore::getMusicPath(id);
	string audio_error = "";
	if (file_music.compare("") == 0) {
		string msg = "Music for ID \"" + id + "\" not configured or file not found";
		this->logger.warn(msg);
	} else {
		this->music = Mix_LoadMUS(file_music.c_str());
		if (this->music == nullptr) {
			audio_error = Mix_GetError();
			if (audio_error.compare("") == 0) {
				audio_error = "Failed to load music: \"" + file_music + "\"";
			}
			this->logger.warn(audio_error);
		}

		if (Mix_PlayMusic(this->music, -1) != 0) {
			audio_error = Mix_GetError();
			if (audio_error.compare("") == 0) {
				audio_error = "Failed to play music: \"" + file_music + "\"";
			}
			this->logger.warn(audio_error);
		}
	}
}

void GameWindow::stopMusic() {
	Mix_HaltMusic();
	Mix_FreeMusic(this->music);
	this->music = nullptr;
}

void GameWindow::shutdown() {
	this->stopMusic();
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	this->viewport->shutdown();
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}
