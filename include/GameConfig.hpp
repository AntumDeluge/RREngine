
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GAME_CONFIG
#define RRE_GAME_CONFIG

#include <cstdint> // *int*_t
#include <string>

#include "Movie.hpp"


/**
 * Namespace for loading & accessing game configuration from `data/conf/game.xml`.
 */
namespace GameConfig {

	/**
	 * Loads game configuration from `data/conf/game.xml` into memory.
	 *
	 * @return
	 *   Return code (0 if completed without errors).
	 */
	int load();

	/**
	 * Retrieves configured game title.
	 *
	 * @return
	 *   Text to display in window title bar.
	 */
	std::string getTitle();

	/**
	 * Retrieves configured game scaling.
	 *
	 * @return
	 *   Multiplier by which window should be scaled.
	 */
	uint16_t getScale();

	/**
	 * Retrieves intro movie.
	 *
	 * @return
	 *   Movie to play at game startup or `null` if not configured.
	 */
	Movie* getIntro();

	/**
	 * Retrieves a configured background image ID for a menu.
	 *
	 * TODO: rename to getMenuBackgroundId
	 *
	 * @param id
	 *   Menu identifier.
	 * @return
	 *   Background identifier or empty string if not configured.
	 */
	std::string getBackground(std::string id);

	/**
	 * Retrieves a configured music ID for a menu.
	 *
	 * @param id
	 *   Menu Identifier.
	 * @return
	 *   Music identifier or empty string if not configured.
	 */
	std::string getMenuMusicId(std::string id);

	/**
	 * Retrieves configured step delay for game.
	 *
	 * @return
	 *   Step delay in milliseconds.
	 */
	uint32_t getStepDelay();
};

#endif /* RRE_GAME_CONFIG */
