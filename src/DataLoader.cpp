/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include "AudioStore.h"
#include "DataLoader.h"
#include "FontMapLoader.h"
#include "Logger.h"
#include "SceneStore.h"

#if HAVE_FONTMAP_PNG_H
#include "builtin/tileset/fontmap_png.h"
#endif

namespace DataLoader {
	bool loaded = false;
};

void buildBuiltinFontMap();

bool DataLoader::load() {
	Logger logger = Logger::getLogger("DataLoader");

	if (DataLoader::loaded) {
		logger.warn("Data already loaded");
		return true;
	}

	if (!FontMapLoader::loadConfig()) {
		return false;
	}

	if (!AudioStore::load()) {
		return false;
	}

	if (!SceneStore::load()) {
		return false;
	}

#if HAVE_FONTMAP_PNG_H
	buildBuiltinFontMap();
#endif

	DataLoader::loaded = true;
	return true;
}

void buildBuiltinFontMap() {
	Logger logger = Logger::getLogger("DataLoader");

#if RRE_DEBUGGING
	logger.debug("Building built-in font map ...");
#endif

	// TODO:
}
