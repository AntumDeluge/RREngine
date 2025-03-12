/* Copyright © 2020-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_AUDIO_STORE
#define RRE_AUDIO_STORE

#include <string>


/**
 * Caches audio paths from configuration.
 */
namespace AudioStore {

	/**
	 * Loads music file paths from data/music directory.
	 *
	 * @return
	 *   `true` if loading succeeded.
	 */
	bool load();

	/**
	 * Retrieves configured path to music file.
	 *
	 * @param id
	 *   Music file identifier (path relative to data/music directory).
	 * @return
	 *   Absolute path to music file.
	 */
	std::string getMusicPath(const std::string id);
}

#endif /* RRE_AUDIO_STORE */
