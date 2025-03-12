/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include "AudioStore.h"
#include "DataLoader.h"
#include "FontMap.h"
#include "FontMapLoader.h"
#include "FontStore.h"
#include "Logger.h"
#include "SceneStore.h"
#include "SingletonRepo.h"
#include "store/EntityStore.hpp"
#include "store/SpriteStore.hpp"


namespace DataLoader {
	bool loaded = false;
};

bool DataLoader::load() {
	Logger logger = Logger::getLogger("DataLoader");

	if (DataLoader::loaded) {
		logger.warn("Data already loaded");
		return true;
	}

	if (!FontMapLoader::loadConfig()) {
		return false;
	}

#if HAVE_BUILTIN_FONT_MAP
	if (!FontMapLoader::loadBuiltin()) {
		return false;
	}
#endif

	FontMap* font_main = FontStore::getMap("main");
	if (font_main != nullptr) {
		GetViewport()->setFontMap(font_main);
	}

	if (!AudioStore::load()) {
		return false;
	}

	if (!SpriteStore::load()) {
		return false;
	}

	if (!EntityStore::load()) {
		return false;
	}

	if (!SceneStore::load()) {
		return false;
	}

	DataLoader::loaded = true;
	return true;
}
