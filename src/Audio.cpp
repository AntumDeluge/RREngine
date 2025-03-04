/* Copyright © 2020-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <unordered_map>

using namespace std;

#include <tinyxml2.h>

using namespace tinyxml2;

#include "Audio.h"
#include "Filesystem.h"
#include "Logger.h"
#include "Path.h"


namespace Audio {
	Logger* logger = Logger::getLogger("Audio");

	bool loaded = false;

	unordered_map<string, string> music_paths;
}

bool Audio::load() {
	if (Audio::loaded) {
		Audio::logger->warn("Audio already loaded");
		return true;
	}

	string dir_music = Path::rabs("data/music");

	for (filesystem::directory_entry item: Filesystem::listDir(dir_music, true)) {
		if (!item.is_regular_file()) {
			continue;
		}
		string p = item.path().string();
		if (p.ends_with(".oga") || p.ends_with(".ogg")) {
			int d_len = dir_music.length();
			string id = p.substr(d_len + 1, p.length() - d_len - 5);
			Audio::music_paths[id] = p;

#if RRE_DEBUGGING
			Audio::logger->debug("Loaded music with ID \"" + id + "\" (" + p + ")");
#endif
		}
	}

	// TODO: load sound effects

	Audio::loaded = true;
	return true;
}

string Audio::getMusicPath(const string id) {
	if (Audio::music_paths.find(id) != Audio::music_paths.end()) {
		return Audio::music_paths[id];
	}
	Audio::logger->warn("Music with ID \"" + id + "\" not loaded");
	return "";
}
