/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <chrono>

//~ #include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//~ #include <cstdio>

#include "audio.h"
#include "dialog.h"
#include "frame.h"
//~ #include "music.h"
#include "paths.h"
#include "reso.h"
#include "singletons.h"
//~ #include "sprite.h"

using namespace std::chrono;


const Uint8 SCREEN_FPS = 60;
const Uint8 SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


unsigned long getTimeMilliseconds() {
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	return ms.count();
}

// initialize singleton instance
GameWindow* GameWindow::instance = nullptr;

GameWindow::GameWindow() {
	this->window = nullptr;
	this->viewport = nullptr;
	this->music = nullptr;
}

void GameWindow::setTitle(const std::string title) {
	SDL_SetWindowTitle(this->window, title.c_str());
}

int GameWindow::init(const std::string title, const int width, const int height) {
	// initialize video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		// NOTE: message logged to console as video subsystem failed to initialize
		Dialog::error(SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// create the SDL frame & viewport renderer
	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height, SDL_WINDOW_SHOWN);
	this->viewport = GetViewPort();
	this->viewport->init(this->window);

	// initialize audio subsystem
	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		Dialog::error(SDL_GetError());
		this->shutdown();
		return 1;
	}

	// initialize mixer for playing OGG audio files
	const int flags = MIX_INIT_OGG;
	const int initted = Mix_Init(flags);
	if (initted&flags != flags) {
		Dialog::error(Mix_GetError());
		this->shutdown();
		return 1;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
		Dialog::error(Mix_GetError());
		this->shutdown();
		return 1;
	}

	// example sprite
	std::string sprite_file = concatPath(dir_root, "data/sprite/character.png");
	SDL_Texture* sprite = nullptr;
	SDL_Surface* surface = IMG_Load(sprite_file.c_str());
	SDL_Rect sprite_rect;
	if (surface == nullptr) {
		Dialog::error("Failed to load surface");
	} else {
		sprite = SDL_CreateTextureFromSurface(this->viewport->getRenderer(), surface);
		sprite_rect = surface->clip_rect;
		SDL_FreeSurface(surface);
	}

	//~ Sprite sp = Sprite();
	//~ sp.setImage("character", 32, 32, window);
	//~ std::string sprite_file = sp->getImage();

	// renderer
	SDL_Renderer* renderer = this->viewport->getRenderer();
	//~ SDL_SetRenderDrawColor(renderer, 0, 0, 20, SDL_ALPHA_OPAQUE);

	unsigned int idx_x = 0;
	unsigned int idx_y = 1;

	SDL_Rect src_rect;
	SDL_Rect tgt_rect;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = 32;
	src_rect.h = 32;

	tgt_rect.x = 0;
	tgt_rect.y = 0;
	tgt_rect.w = src_rect.w;
	tgt_rect.h = src_rect.h;

	// face profile
	SDL_Rect p_rect_src;
	SDL_Rect p_rect_tgt;

	p_rect_src.x = 32 * 5;
	p_rect_src.y = 0;
	p_rect_src.w = 32;
	p_rect_src.h = 32;

	p_rect_tgt.x = width / 2 - 16;
	p_rect_tgt.y = height / 2 - 16;
	p_rect_tgt.w = 32;
	p_rect_tgt.h = 32;

	bool rev = false;
	unsigned int iter = 0;

	int dir;
	int lastpress = 1;

	this->playMusic("main");

	// main loop flag
	bool quit = false;

	// event handler
	SDL_Event event;

	unsigned long last_draw_time = getTimeMilliseconds();

	// TODO: move game loop to singleton class
	while (!quit) {
		unsigned long elapsed_ms = last_draw_time - getTimeMilliseconds();

		dir = 0;
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else {
				//dir = 2;
				/*
				SDL_Keycode keycode = event.key.keysym.sym;
				if (keycode == SDLK_LEFT) {
					dir = 1;
				} else if (keycode == SDLK_RIGHT) {
					dir = 2;
				}
				*/
			}
		}

		// DEBUG:
		//~ this->viewport->draw(sprite, sprite_rect);
		//~ continue;

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_LEFT]) {
			dir = 1;
			lastpress = 0;
		} else if (state[SDL_SCANCODE_RIGHT]) {
			dir = 2;
			lastpress = 1;
		}

		//~ //printf("Direction: %i\n", dir);

		if (dir == 0) {
			idx_x = 0;
			//idx_y = 1;
			rev = false;
		} else {
			if (idx_x == 0) {
				idx_x = 2;
			}

			if (idx_x == 3) {
				rev = false;
			} else if (idx_x == 5) {
				rev = true;
			}

			if (rev) {
				idx_x--;
			} else {
				idx_x++;
			}
		}

		if (iter >= 100000) {
		//~ if (iter >= SCREEN_TICKS_PER_FRAME) {
			iter = 0;

			// FIXME: doesn't work to limit movement/redraw
			/*
			if (elapsed_ms < 5000) {
				continue;
			} else {
				last_draw_time = getTimeMilliseconds();
			}
			*/

			src_rect.x = src_rect.w * idx_x;
			src_rect.y = src_rect.h * idx_y;

			SDL_RendererFlip flip = SDL_FLIP_NONE;
			if (lastpress == 0) {
				flip = SDL_FLIP_HORIZONTAL;
			}

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, sprite, &p_rect_src, &p_rect_tgt);
			SDL_RenderCopyEx(renderer, sprite, &src_rect, &tgt_rect, 0, NULL, flip);
			SDL_RenderPresent(renderer);

			if (tgt_rect.x > width - src_rect.w) {
				tgt_rect.x = 0;
				if (tgt_rect.y >= height - src_rect.h) {
					tgt_rect.y = 0;
				} else {
					tgt_rect.y += src_rect.h;
				}
			} else if (tgt_rect.x < 0) {
				tgt_rect.x = width - src_rect.w;
				if (tgt_rect.y == 0) {
					tgt_rect.y = height - src_rect.h;
				}
			} else {
				if (dir != 0) {
					int distance = src_rect.w / 4;
					if (dir == 1) {
						distance = distance * -1;
					}

					tgt_rect.x += distance;
				}
			}
		} else {
			iter++;
		}
	}

	SDL_DestroyTexture(sprite);
	this->shutdown();

	return 0;
}

int GameWindow::init() {
	return this->init("R&R Engine", RES1.first, RES1.second);
}

void GameWindow::playMusic(std::string id) {
	if (Mix_PlayingMusic() != 0) {
		// close previous stream
		this->stopMusic();
	}

	std::string file_music = Audio::GetMusicFile(id);
	std::string audio_error = "";
	if (file_music.compare("") == 0) {
		Dialog::warn("Music for ID \"" + id + "\" not configured or file not found");
	} else {
		this->music = Mix_LoadMUS(file_music.c_str());
		if (this->music == nullptr) {
			audio_error = Mix_GetError();
			if (audio_error.compare("") == 0) {
				audio_error = "Failed to load music: \"" + file_music + "\"";
			}
			Dialog::warn(audio_error);
		}

		if (Mix_PlayMusic(this->music, -1) != 0) {
			audio_error = Mix_GetError();
			if (audio_error.compare("") == 0) {
				audio_error = "Failed to play music: \"" + file_music + "\"";
			}
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
