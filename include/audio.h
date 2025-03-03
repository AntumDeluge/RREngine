/* Copyright © 2020-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_AUDIO_H
#define RRE_AUDIO_H

#include <string>


namespace Audio {
	// @deprecated Use GameConfig::getMusic(id)
	extern std::string GetMusicFile(const std::string id);
}

#endif /* RRE_AUDIO_H */
