
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GAME_LOOP
#define RRE_GAME_LOOP

#include "GameMode.h"


namespace GameLoop {

	void start();

	void end();

	GameMode::Mode getMode();

	void setMode(GameMode::Mode mode);
};

#endif /* RRE_GAME_LOOP */
