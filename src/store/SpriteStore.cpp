/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <memory>
#include <unordered_map>

#include <tinyxml2.h>

#include "Dialog.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "factory/SpriteFactory.hpp"
#include "store/SpriteStore.hpp"

using namespace std;
using namespace tinyxml2;


static Logger _logger = Logger::getLogger("SpriteStore");

/** Holds loaded sprites in memory indexed by ID/path. */
static unordered_map<string, shared_ptr<Sprite>> _cache;

static void _onConfigError(string title, string msg) {
	if (!title.empty()) {
		_logger.error(title + ": " + msg);
		Dialog::error(title, msg);
	} else {
		_logger.error(msg);
		Dialog::error(msg);
	}
}

static void _onConfigError(string msg) {
	_onConfigError("", msg);
}

bool SpriteStore::load() {
	string conf = Path::rabs("data/conf/sprites.xml");
	if (!Filesystem::fexist(conf)) {
		_logger.warn("Sprite configuration not found: " + conf);
		// don't halt execution
		return true;
	}

	XMLDocument doc;
	if (doc.LoadFile(conf.c_str()) != XML_SUCCESS) {
		_onConfigError("Failed to load sprite configuration: " + conf);
		return false;
	}

	XMLElement* root = doc.FirstChildElement("sprites");
	if (root == nullptr) {
		_onConfigError("XML Parsing Error", "Root tag \"sprites\" not found: " + conf);
		return false;
	}

	XMLElement* el = root->FirstChildElement("sprite");
	while (el != nullptr) {
		const XMLAttribute* attr_id = el->FindAttribute("id");
		if (attr_id == nullptr) {
			_onConfigError("XML Parsing Error", "Sprite tag without \"id\" attribute: " + conf);
			return false;
		}
		string id = attr_id->Value();
		shared_ptr<Sprite> sprite_ptr = SpriteFactory::build(el);
		if (!sprite_ptr || !sprite_ptr->ready()) {
			_onConfigError("Failed to load sprite \"" + id + "\": " + conf);
			return false;
		}
		// add to cache
		_cache[id] = sprite_ptr;

		el = el->NextSiblingElement("sprite");
	}

	return true;
}

Sprite* SpriteStore::get(string id) {
	Sprite* sprite;
	// check cache first
	if (_cache.find(id) != _cache.end()) {
		sprite = _cache[id].get();
		if (!sprite->ready()) {
			_logger.warn("Returning uninitialized sprite: " + id);
		}
	} else {
		// if not cached an uninitialized sprite is returned
		_logger.warn("Sprite not available: " + id);
	}
	return sprite;
}
