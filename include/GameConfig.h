
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GAME_CONFIG
#define RRE_GAME_CONFIG

#include <cstdint> // uint*_t
#include <string>


namespace GameConfig {

	int load();

	std::string getTitle();

	uint16_t getScale();

	std::string getBackground(std::string id);

	std::string getMenuMusicId(std::string id);
};

#endif /* RRE_GAME_CONFIG */
