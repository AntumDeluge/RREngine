
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GAME_LOOP
#define RRE_GAME_LOOP

#include <string>

#include "enum/GameMode.hpp"


/**
 * Handles draw rate & stepping of game logic.
 */
namespace GameLoop {

	/**
	 * Starts the game loop & initializes game mode.
	 */
	void start();

	/**
	 * Marks game loop for ending & clean up.
	 */
	void end();

	/**
	 * Retrieves current game mode.
	 *
	 * @return
	 *   Game mode.
	 */
	GameMode::Mode getMode();

	/**
	 * Updates current game mode.
	 *
	 * @param mode
	 *   New game mode.
	 */
	void setMode(GameMode::Mode mode);

	/**
	 * Toggles paused state of game loop.
	 *
	 * @param pause
	 *   Set to `true` disable completion of loop, `false` to re-enable.
	 * @param id
	 *   Identifier of source of pause.
	 */
	void setPaused(bool pause, std::string id="");

	/**
	 * Checks paused state of game loop.
	 *
	 * If `id` defined, checks if paused by ID source.
	 *
	 * @param id
	 *   Identifier of source of pause.
	 * @return
	 *   `true` if loop is considered to be paused.
	 */
	bool isPaused(std::string id="");
};

#endif /* RRE_GAME_LOOP */
