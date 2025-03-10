
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <cstdint> // uint*_t
#if RRE_DEBUGGING
#include <string>

using namespace std;
#endif

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Dialog.hpp"
#include "GameLogic.hpp"
#include "GameLoop.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "SingletonRepo.hpp"
#include "Viewport.hpp"
#include "reso.hpp"


namespace GameLoop {
	// logger instance
	Logger logger = Logger::getLogger("GameLoop");

	GameMode::Mode mode = GameMode::NONE;
}

// loop iterator flag
bool quit = false;

void GameLoop::start() {
#if RRE_DEBUGGING
	GameLoop::logger.debug("Starting game loop ...");
#endif

	Viewport* viewport = GetViewport();
	GameLogic* logic = GetGameLogic();

	// most recent input event
	SDL_Event event;

	// delay (in milliseconds) for each game logic step
	uint16_t step_interval = logic->getStepDelay();
	// time (in milliseconds) at which game logic was most recently executed
	uint64_t time_prev = SDL_GetTicks64();

	// target redraw rate
	// TODO: use settings to set FPS limit
	float fps_limit = 29.97 * 2;
	// delay (in milliseconds) for each viewport redraw
	float draw_interval = 1000 / fps_limit;
	// time (in milliseconds) at which viewport was most recently redrawn
	uint64_t last_draw_time = 0;

#if RRE_DEBUGGING
	GameLoop::logger.debug("Game logic step interval: " + to_string(step_interval) + "ms");

	// number of frames drawn during this interval
	uint16_t f_drawn = 0;
	// time at which current draw interval started
	uint64_t fcount_start = time_prev;
#endif

	// set before drawing to show FPS before update
	viewport->setCurrentFPS(0);


	/* *** START: TESTING EXAMPLE *** */

	// renderer
	SDL_Renderer* renderer = viewport->getRenderer();

	string sprite_file = Path::rabs("data/sprite/character.png");
	SDL_Texture* sprite = nullptr;
	SDL_Surface* surface = IMG_Load(sprite_file.c_str());
	SDL_Rect sprite_rect;
	if (surface == nullptr) {
		Dialog::error("Failed to load surface");
	} else {
		sprite = SDL_CreateTextureFromSurface(renderer, surface);
		sprite_rect = surface->clip_rect;
		SDL_FreeSurface(surface);
	}

	int width = RES1.first;
	int height = RES1.second;

	uint32_t idx_x = 0;
	uint32_t idx_y = 1;

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
	uint32_t iter = 0;

	int lastpress = 1;

	viewport->addText("press enter");

	/* *** END: TESTING EXAMPLE *** */


	// start with intro movie if configured
	GameLoop::setMode(GameMode::INTRO);

	while (!quit) {
		// time (in milliseconds) at which game loop is executing
		uint64_t time_now = SDL_GetTicks64();
		// elapsed time (in milliseconds) since game logic was last executed
		uint16_t time_elapsed = time_now - time_prev;

		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				GameLoop::end();
			} else if (event.type == SDL_KEYDOWN) {
				GetInput()->onKeyDown(event.key.keysym);
			} else if (event.type == SDL_KEYUP) {
				GetInput()->onKeyUp(event.key.keysym);
			}
		}

		const uint8_t* k_state = SDL_GetKeyboardState(NULL);

		if (GameLoop::mode == GameMode::TITLE) {
			// TODO: use translated event to determine how to proceed
			if (k_state[SDL_SCANCODE_RETURN] || k_state[SDL_SCANCODE_KP_ENTER]) {
				GameLoop::setMode(GameMode::SCENE);
			}
		}


		/* ** START: TESTING EXAMPLE ** */

		// eventually will be done in GameLogic.step

		if (GameLoop::mode == GameMode::SCENE) {
			if (iter >= 100000) {
				iter = 0;

				int dir = 0;
				const Uint8* state = SDL_GetKeyboardState(NULL);
				if (state[SDL_SCANCODE_LEFT]) {
					dir = 1;
					lastpress = 0;
				} else if (state[SDL_SCANCODE_RIGHT]) {
					dir = 2;
					lastpress = 1;
				}

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

				src_rect.x = src_rect.w * idx_x;
				src_rect.y = src_rect.h * idx_y;

				SDL_RendererFlip flip = SDL_FLIP_NONE;
				if (lastpress == 0) {
					flip = SDL_FLIP_HORIZONTAL;
				}

				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, sprite, &p_rect_src, &p_rect_tgt);
				SDL_RenderCopyEx(renderer, sprite, &src_rect, &tgt_rect, 0, NULL, flip);
				//~ SDL_RenderPresent(renderer);
				viewport->draw();

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

		/* ** END: TESTING EXAMPLE ** */


		// limit game stepping frequency to defined millisecond intervals
		// FIXME: should step only occur in GameMode::SCENE?
		if (time_elapsed >= step_interval) {
			logic->step(time_now);
			time_prev = time_now;
		}

		// limit viewport redraw frequency to configured max FPS
		if (time_now - last_draw_time >= draw_interval) {
			// DEBUG:
			if (GameLoop::mode != GameMode::SCENE) {
				SDL_RenderClear(renderer);
				viewport->draw();
			}
			last_draw_time = time_now;
#if RRE_DEBUGGING
			f_drawn++;
		}

		if (time_now - fcount_start >= 1000) {
			// update FPS after 1 second
			viewport->setCurrentFPS(f_drawn);
			// restart counter
			f_drawn = 0;
			fcount_start = time_now;
#endif
		}
	}

	SDL_DestroyTexture(sprite);
}

void GameLoop::end() {
	quit = true;
}

GameMode::Mode GameLoop::getMode() {
	return GameLoop::mode;
}

void GameLoop::setMode(GameMode::Mode mode) {
	GameLoop::mode = mode;
	GetViewport()->setMode(GameLoop::mode);
}
