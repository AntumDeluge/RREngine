
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <cstdint> // *int*_t

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>

#include "GameLogic.hpp"
#include "GameLoop.hpp"
#include "Logger.hpp"
#include "SingletonRepo.hpp"
#include "impl/ViewportImpl.hpp"

using namespace std;


namespace GameLoop {
	// logger instance
	Logger logger = Logger::getLogger("GameLoop");

	GameMode::Mode mode = GameMode::NONE;
}

// loop iterator flag
static bool quit = false;

// pause loop flag
static bool paused = false;
// ID of source of pause
static string pause_id = "";

void GameLoop::start() {
#if RRE_DEBUGGING
	GameLoop::logger.debug("Starting game loop ...");
#endif

	ViewportImpl* viewport = GetViewport();
	GameLogic* logic = GetGameLogic();

	// most recent input event
	SDL_Event event;

	// delay (in milliseconds) for each game logic step
	uint32_t step_interval = logic->getStepDelay();
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
	GameLoop::logger.debug("Game logic step interval: ", to_string(step_interval), "ms");

	// number of frames drawn during this interval
	uint16_t f_drawn = 0;
	// time at which current draw interval started
	uint64_t fcount_start = time_prev;
#endif

	// set before drawing to show FPS before update
	viewport->setCurrentFPS(0);

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
				GetInput()->onKeyDown(event.key.keysym.sym);
			} else if (event.type == SDL_KEYUP) {
				GetInput()->onKeyUp(event.key.keysym.sym);
			} else if (event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP) {
				GetInput()->translateGamepadButtonEvent(event.jbutton.button, event.jbutton.state);
			} else if (event.type == SDL_JOYHATMOTION) {
				GetInput()->translateGamepadHatEvent(event.jhat);
			} else if (event.type == SDL_JOYAXISMOTION) {
				GetInput()->translateGamepadAxisEvent(event.jaxis);
			}
		}

		// don't complete loop until unpaused
		if (paused) continue;

		const uint8_t* k_state = SDL_GetKeyboardState(NULL);

		if (GameLoop::mode == GameMode::TITLE) {
			// TODO: use translated event to determine how to proceed
			if (k_state[SDL_SCANCODE_RETURN] || k_state[SDL_SCANCODE_KP_ENTER]) {
				GameLoop::setMode(GameMode::SCENE);
			}
		}

		// limit game stepping frequency to defined millisecond intervals
		// FIXME: should step only occur in GameMode::SCENE?
		if (time_elapsed >= step_interval) {
			logic->step(time_now);
			time_prev = time_now;
		}

		// limit viewport redraw frequency to configured max FPS
		if (time_now - last_draw_time >= draw_interval) {
			viewport->render();
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
}

void GameLoop::end() {
	quit = true;
}

GameMode::Mode GameLoop::getMode() {
	return GameLoop::mode;
}

void GameLoop::setMode(GameMode::Mode mode) {
	GameLoop::mode = mode;
	GetViewport()->setRenderMode(GameLoop::mode);
}

void GameLoop::setPaused(bool pause, string id) {
	paused = pause;
	if (pause) {
		pause_id = id;
	} else {
		// always reset when unpausing
		pause_id = "";
	}
}

bool GameLoop::isPaused(string id) {
	if (id != "") {
		return id == pause_id && paused;
	}
	return paused;
}
