/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "AudioStore.h"
#include "DataLoader.h"
#include "Logger.h"
#include "TMXLoader.h"


namespace DataLoader {
	bool loaded = false;
};

bool DataLoader::load() {
	Logger* logger = Logger::getLogger("DataLoader");

	if (DataLoader::loaded) {
		logger->warn("Data already loaded");
		return true;
	}

	if (!AudioStore::load()) {
		return false;
	}

	if (!TMXLoader::load()) {
		return false;
	}

	DataLoader::loaded = true;
	return true;
}
