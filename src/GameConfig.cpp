
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <unordered_map>

using namespace std;

#include <tinyxml2.h>

using namespace tinyxml2;

#include "Dialog.h"
#include "Filesystem.h"
#include "GameConfig.h"
#include "Logger.h"
#include "Path.h"


namespace GameConfig {
	Logger* logger = Logger::getLogger("GameConfig");
}

string game_conf = Path::join(Path::dir_root, "data/conf/game.xml");

// configured options
string title = "";
uint16_t scale = 1;
unordered_map<string, string> menu_backgrounds;
unordered_map<string, string> menu_music;

bool loaded = false;

void onConfigError(string title, string msg) {
	msg += ": \"" + game_conf + "\"";
	GameConfig::logger->error(msg);
	Dialog::error(title, msg);
}

void onConfigError(string msg) {
	onConfigError("Error", msg);
}

int GameConfig::load() {
	if (loaded) {
		GameConfig::logger->warn("Game configuration already loaded");
		return 0;
	}

	if (!Filesystem::fexist(game_conf)) {
		onConfigError("Game configuration not found");
		// TODO: use errno standard
		return 1;
	}

	XMLDocument doc;
	if (doc.LoadFile(game_conf.c_str()) != 0) {
		onConfigError("XML Loading Error", "Failed to load game configuration");
		return 1;
	}

	XMLElement* el_root = doc.RootElement();
	if (el_root == nullptr) {
		onConfigError("XML Parsing Error", "Root element not found");
		return 1;
	}

	XMLElement* el_title = el_root->FirstChildElement("title");
	if (el_title == nullptr) {
		GameConfig::logger->warn("Game title not configured");
	} else {
		title = el_title->GetText();
	}
	if (title.compare("") == 0) {
		// default title
		title = "R&R Engine";
	}

	XMLElement* el_scale = el_root->FirstChildElement("scale");
	if (el_scale != nullptr && el_scale->QueryUnsignedText((uint32_t*) &scale) != 0) {
		onConfigError("XML Parsing Error", "\"scale\" value must be integer");
		return 1;
	}
	if (scale == 0) {
		GameConfig::logger->warn("Scale must be a positive integer");
		scale = 1;
	}
	if (scale > 4) {
		GameConfig::logger->warn("Currently scaling the game window more than 4x is not supported");
		scale = 4;
	}

	XMLElement* el_menu = el_root->FirstChildElement("menu");
	while (el_menu != nullptr) {
		const XMLAttribute* attr_id = el_menu->FindAttribute("id");
		if (attr_id == nullptr) {
			onConfigError("XML Parsing Error", "\"menu\" element without \"id\" attribute");
			return 1;
		}

		string id = attr_id->Value();
		if (id.compare("") == 0) {
			onConfigError("XML Parsing Error", "\"id\" attribute without value");
			return 1;
		}

		const XMLAttribute* attr_bg = el_menu->FindAttribute("background");
		if (attr_bg == nullptr) {
			GameConfig::logger->warn("Menu (" + id + ") without background");
		} else {
			menu_backgrounds[id] = Path::join(Path::dir_root + "/data/menu", string(attr_bg->Value())
					+ ".png");
		}

		const XMLAttribute* attr_music = el_menu->FindAttribute("music");
		if (attr_music == nullptr) {
			GameConfig::logger->warn("Menu (" + id + ") without music");
		} else {
			string music_path = Path::join(Path::dir_root + "/data/music", string(attr_music->Value()));
			if (Filesystem::fexist(music_path + ".oga")) {
				music_path += ".oga";
			} else {
				music_path += ".ogg";
			}
			menu_music[id] = music_path;
		}

		el_menu = el_menu->NextSiblingElement("menu");
	}

	// TODO: add option for aspect ratio

	loaded = true;
	return 0;
}

string GameConfig::getTitle() {
	return title;
}

uint16_t GameConfig::getScale() {
	return scale;
}

string GameConfig::getBackground(string id) {
	if (menu_backgrounds.find(id) != menu_backgrounds.end()) {
		return menu_backgrounds[id];
	}
	return "";
}

string GameConfig::getMusic(string id) {
	if (menu_music.find(id) != menu_music.end()) {
		return menu_music[id];
	}
	return "";
}
