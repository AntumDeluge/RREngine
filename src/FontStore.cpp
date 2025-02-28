/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "FontStore.h"
#include "Logger.h"


// font map cache
std::unordered_map<std::string, FontMap*> fmap_cache = {};

void FontStore::addMap(std::string fid, FontMap* fmap) {
	if (fmap_cache.find(fid) != fmap_cache.end()) {
		Logger::getLogger("FontStore")->warn("Overwriting font map with id \"" + fid + "\"");
	}
	fmap_cache[fid] = fmap;
}

FontMap* FontStore::getMap(std::string fid) {
	if (fmap_cache.find(fid) != fmap_cache.end()) {
		return fmap_cache[fid];
	}
	return nullptr;
}
