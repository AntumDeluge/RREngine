/* Copyright © 2020-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <unordered_map>

#include "Filesystem.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "store/AudioStore.hpp"

using namespace std;


namespace AudioStore {
	Logger logger = Logger::getLogger("AudioStore");

	bool loaded = false;

	unordered_map<string, string> music_paths;
}

bool AudioStore::load() {
	if (AudioStore::loaded) {
		AudioStore::logger.warn("Audio data already loaded");
		return true;
	}

	string dir_music = Path::rabs("data/music");
	if (!filesystem::is_directory(dir_music)) {
		logger.warn("Music data directory not found: ", dir_music);
	} else {
		for (filesystem::directory_entry item: Filesystem::listDir(dir_music, true)) {
			if (!item.is_regular_file()) {
				continue;
			}
			string p = item.path().string();
			if (p.ends_with(".oga") || string(p).ends_with(".ogg")) {
				int d_len = dir_music.length();
				string id = p.substr(d_len + 1, p.length() - d_len - 5); // @suppress("Invalid arguments")
				AudioStore::music_paths[id] = p;

#if RRE_DEBUGGING
				AudioStore::logger.debug("Loaded music with ID \"", id, "\" (", p, ")");
#endif
			}
		}
	}

	// TODO: load sound effects

	AudioStore::loaded = true;
	return true;
}

string AudioStore::getMusicPath(const string id) {
	if (AudioStore::music_paths.find(id) != AudioStore::music_paths.end()) {
		return AudioStore::music_paths[id];
	}
	AudioStore::logger.warn("Music with ID \"", id, "\" not loaded");
	return "";
}
