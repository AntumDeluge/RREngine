
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GAME_LOOP
#define RRE_GAME_LOOP

#include "GameMode.hpp"


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
};

#endif /* RRE_GAME_LOOP */
