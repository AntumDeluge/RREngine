/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <unordered_map>

#include <tinyxml2.h>

#include "Dialog.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "factory/EntityFactory.hpp"
#include "store/EntityStore.hpp"

using namespace std;
using namespace tinyxml2;


static Logger _logger = Logger::getLogger("EntityStore");

// base entities to make copies
static unordered_map<string, Entity> _cache;

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

bool EntityStore::load() {
	string conf = Path::rabs("data/conf/entities.xml");
	if (!Filesystem::fexist(conf)) {
		_onConfigError("Configuration not found: " + conf);
		// don't halt process
		return true;
	}

	XMLDocument doc;
	if (doc.LoadFile(conf.c_str()) != XML_SUCCESS) {
		_onConfigError("Failed to load config: " + conf);
		return false;
	}

	XMLElement* root = doc.FirstChildElement("entities");
	if (!root) {
		_onConfigError("XML Parsing Error", "Root element \"entities\" not found: " + conf);
		return false;
	}

	XMLElement* el = root->FirstChildElement("entity");
	while (el) {
		const XMLAttribute* attr_id = el->FindAttribute("id");
		if (!attr_id) {
			_onConfigError("XML Parsing Error", "Entity without \"id\" attribute: " + conf);
			return false;
		}
		string id = attr_id->Value();
		Entity e = EntityFactory::build(el);
		if (e == NullEntity) {
			_onConfigError("Failed to build Entity \"" + id + "\": " + conf);
			return false;
		}
		_cache[id] = e;

		el = el->NextSiblingElement("entity");
	}

	return true;
}

Entity EntityStore::getEntity(string id) {
	if (_cache.find(id) == _cache.end()) {
		_logger.error("Entity \"" + id + "\" not available");
		return NullEntity;
	}
	return _cache[id];
}
