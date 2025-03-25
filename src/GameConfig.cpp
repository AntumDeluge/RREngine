
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <unordered_map>

#include <pugixml.hpp>

#include "Dialog.hpp"
#include "Filesystem.hpp"
#include "GameConfig.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "StrUtil.hpp"
#include "factory/MovieFactory.hpp"

using namespace pugi;
using namespace std;


namespace GameConfig {
	Logger logger = Logger::getLogger("GameConfig");

	// path to master game configuration
	const string file_conf = Path::rabs("data/conf/game.xml");
}

// configured options
// TODO:
// - move into GameConfig namespace
// - make static?
string title = "";
uint16_t scale = 1;
static uint32_t step_delay = 300;
unordered_map<string, string> menu_backgrounds;
unordered_map<string, string> menu_music_ids;
string intro_id = "";

bool loaded = false;

void onConfigError(string title, string msg) {
	msg += ": \"" + GameConfig::file_conf + "\"";
	GameConfig::logger.error(msg);
	Dialog::error(title, msg);
}

void onConfigError(string msg) {
	onConfigError("Error", msg);
}

int GameConfig::load() {
	if (loaded) {
		GameConfig::logger.warn("Game configuration already loaded");
		return 0;
	}

	if (!Filesystem::fexist(GameConfig::file_conf)) {
		GameConfig::logger.warn("Game configuration not found: \"", GameConfig::file_conf, "\"");
		return 0;
	}

	xml_document doc;
	if (doc.load_file(GameConfig::file_conf.c_str()).status != status_ok) {
		onConfigError("XML Loading Error", "Failed to load game configuration");
		return 1;
	}

	xml_node el_root = doc.child("game");
	if (el_root.type() == node_null) {
		onConfigError("XML Parsing Error", "Root element not found");
		return 1;
	}

	xml_node el_intro = el_root.child("intro");
	if (el_intro.type() != node_null) {
		xml_attribute attr_movie = el_intro.attribute("movie");
		if (attr_movie.empty()) {
			onConfigError("XML Parsing Error",
					"Intro element without \"movie\" attribute");
			return 1;
		}
		intro_id = attr_movie.value();
	}

	xml_node el_title = el_root.child("title");
	if (el_title.type() != node_null) {
		title = el_title.text().get();
	}
	if (title.empty()) {
		GameConfig::logger.warn("Game title not configured");
		title = "R&R Engine " + string(RRE_VERSION);
	}

	xml_node el_scale = el_root.child("scale");
	if (el_scale.type() != node_null) { // && StrUtil::toUint())
		scale = StrUtil::toUInt(el_scale.text().get());
		if (!scale) {
			scale = 1;
			onConfigError("XML Parsing Error", "\"scale\" value must be integer greater than 0");
			return 1;
		}
	}
	if (scale > 4) {
		GameConfig::logger.warn("Currently scaling the game window more than 4x is not supported");
		scale = 4;
	}

	xml_node el_step_delay = el_root.child("step_delay");
	if (el_step_delay.type() != node_null) {
		step_delay = StrUtil::toUInt(el_step_delay.text().get());
	}
	if (!step_delay) {
		GameConfig::logger.warn("Step delay must be a positive integer");
		// reset to default value
		step_delay = 300;
	}

	xml_node el_menu = el_root.child("menu");
	while (el_menu.type() != node_null) {
		xml_attribute attr_id = el_menu.attribute("id");
		if (attr_id.empty()) {
			onConfigError("XML Parsing Error", "\"menu\" element without \"id\" attribute");
			return 1;
		}

		string id = attr_id.value();
		if (id.compare("") == 0) {
			onConfigError("XML Parsing Error", "\"id\" attribute without value");
			return 1;
		}

		xml_attribute attr_bg = el_menu.attribute("background");
		if (attr_bg.empty()) {
			GameConfig::logger.warn("Menu (", id, ") without background");
		} else {
			menu_backgrounds[id] = Path::join("background", attr_bg.value());
		}

		xml_attribute attr_music = el_menu.attribute("music");
		if (attr_music.empty()) {
			GameConfig::logger.warn("Menu (", id, ") without music");
		} else {
			menu_music_ids[id] = attr_music.value();
		}

		el_menu = el_menu.next_sibling("menu");
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

Movie* GameConfig::getIntro() {
	if (intro_id.empty()) {
		return nullptr;
	}
	return MovieFactory::getMovie(intro_id);
}

string GameConfig::getBackground(string id) {
	if (menu_backgrounds.find(id) != menu_backgrounds.end()) {
		return menu_backgrounds[id];
	}
	return "";
}

string GameConfig::getMenuMusicId(string id) {
	if (menu_music_ids.find(id) != menu_music_ids.end()) {
		return menu_music_ids[id];
	}
	return "";
}

uint32_t GameConfig::getStepDelay() {
	return step_delay;
}
