/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <SDL2/SDL.h> // SDL2 defines SDL_Init in main header, this has been moved to SDL_init.h in SDL3

#include "FontStore.h"
#include "GameLogic.h"
#include "GameWindow.h"
#include "SingletonRepo.h"
#include "audio.h"
#include "config.h"
#include "dialog.h"
#include "reso.h"

using namespace std;


// initialize singleton instance
GameWindow* GameWindow::instance = nullptr;

GameWindow::GameWindow() {
	this->logger = Logger::getLogger("GameWindow");
	this->window = nullptr;
	this->viewport = nullptr;
	this->music = nullptr;
	this->quit = false;
}

void GameWindow::setTitle(const string title) {
	SDL_SetWindowTitle(this->window, title.c_str());
}

int GameWindow::init(const string title, const int width, const int height) {
	this->logger->debug("Initializing SDL ...");

	// initialize video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		// NOTE: message logged to console as video subsystem failed to initialize
		string msg = SDL_GetError();
		this->logger->error(msg);
		Dialog::error(msg);
		SDL_Quit();
		return 1;
	}

	// create the SDL frame & viewport renderer
	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height, SDL_WINDOW_SHOWN);
	this->viewport = GetViewport();
	this->viewport->init(this->window);

	// initialize audio subsystem
	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		string msg = SDL_GetError();
		this->logger->error(msg);
		Dialog::error(msg);
		this->shutdown();
		return 1;
	}

	// initialize mixer for playing OGG audio files
	const int flags = MIX_INIT_OGG;
	const int initted = Mix_Init(flags);
	if (initted&flags != flags) {
		string msg = Mix_GetError();
		this->logger->error(msg);
		Dialog::error(msg);
		this->shutdown();
		return 1;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
		string msg = Mix_GetError();
		this->logger->error(msg);
		Dialog::error(msg);
		this->shutdown();
		return 1;
	}

	GetFontMapLoader()->loadConfig();
	this->viewport->setFontMap(FontStore::getMap("main"));

	const GameLogic* logic = GetGameLogic();
	uint16_t step_delay = logic->getStepDelay(); // delay (in milliseconds) for each step

#if RRE_DEBUGGING
	this->logger->debug("Game logic step delay: " + to_string(step_delay) + "ms");
#endif

	// event handler
	SDL_Event event;

	// time (in milliseconds) at which game logic was last executed
	uint64_t time_prev = SDL_GetTicks64();

	// TODO: use settings to set FPS limit
	float fps_limit = 29.97;
	float draw_interval = 1000 / fps_limit;

	uint64_t last_draw_time = 0;

#if RRE_DEBUGGING
	uint16_t f_drawn = 0;
	uint64_t fcount_start = time_prev;
#endif

	// TODO: move game loop to singleton class
	while (!this->quit) {
		// time (in milliseconds) at which game loop is executing
		uint64_t time_now = SDL_GetTicks64();
		// elapsed time (in milliseconds) since game logic was last executed
		uint16_t time_elapsed = time_now - time_prev;

		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				this->endGameLoop();
			}
		}

		// limit game stepping to defined millisecond intervals
		if (time_elapsed >= step_delay) {
			GetGameLogic()->step(time_now);
			time_prev = time_now;
		}

		// limit viewport refresh to configured max FPS
		if (time_now - last_draw_time >= draw_interval) {
			this->viewport->draw();
			last_draw_time = time_now;
#if RRE_DEBUGGING
			f_drawn++;
#endif
		}

#if RRE_DEBUGGING
		if (time_now - fcount_start >= 1000) {
			// check FPS after 1 second
			this->viewport->setCurrentFPS(f_drawn);
			// restart counter
			f_drawn = 0;
			fcount_start = time_now;
		}
#endif
	}

	this->shutdown();

	return 0;
}

int GameWindow::init() {
	return this->init("R&R Engine", RES1.first, RES1.second);
}

void GameWindow::endGameLoop() {
	this->quit = true;
}

void GameWindow::playMusic(string id) {
	if (Mix_PlayingMusic() != 0) {
		// close previous stream
		this->stopMusic();
	}

	string file_music = Audio::GetMusicFile(id);
	string audio_error = "";
	if (file_music.compare("") == 0) {
		string msg = "Music for ID \"" + id + "\" not configured or file not found";
		this->logger->warn(msg);
		Dialog::warn(msg);
	} else {
		this->music = Mix_LoadMUS(file_music.c_str());
		if (this->music == nullptr) {
			audio_error = Mix_GetError();
			if (audio_error.compare("") == 0) {
				audio_error = "Failed to load music: \"" + file_music + "\"";
			}
			this->logger->warn(audio_error);
			Dialog::warn(audio_error);
		}

		if (Mix_PlayMusic(this->music, -1) != 0) {
			audio_error = Mix_GetError();
			if (audio_error.compare("") == 0) {
				audio_error = "Failed to play music: \"" + file_music + "\"";
			}
			this->logger->warn(audio_error);
			Dialog::warn(audio_error);
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
	this->viewport->shutdown();
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}
