/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */


#include "config.h"

#include "DataLoader.hpp"
#include "FontMap.hpp"
#include "Logger.hpp"
#include "SingletonRepo.hpp"
#include "factory/FontMapFactory.hpp"
#include "store/AudioStore.hpp"
#include "store/FontMapStore.hpp"
#include "store/EntityStore.hpp"
#include "store/SceneStore.hpp"
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

	if (!FontMapFactory::loadConfig()) {
		return false;
	}

#if HAVE_BUILTIN_FONT_MAP
	if (!FontMapFactory::loadBuiltin()) {
		return false;
	}
#endif

	FontMap* font_main = FontMapStore::get("main");
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
