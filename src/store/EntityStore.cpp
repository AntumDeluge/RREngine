/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <unordered_map>

#include <pugixml.hpp>

#include "Dialog.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "factory/EntityFactory.hpp"
#include "store/EntityStore.hpp"

using namespace pugi;
using namespace std;


static Logger _logger = Logger::getLogger("EntityStore");

// base entities to make copies
static unordered_map<string, Entity> _cache;

static void _onConfigError(string title, string msg) {
	if (!title.empty()) {
		_logger.error(title, ": ", msg);
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

	xml_document doc;
	if (doc.load_file(conf.c_str()).status != status_ok) {
		_onConfigError("Failed to load config: " + conf);
		return false;
	}

	xml_node root = doc.child("entities");
	if (root.type() == node_null) {
		_onConfigError("XML Parsing Error", "Root element \"entities\" not found: " + conf);
		return false;
	}

	xml_node el = root.child("entity");
	while (el.type() != node_null) {
		xml_attribute attr_id = el.attribute("id");
		if (attr_id.empty()) {
			_onConfigError("XML Parsing Error", "Entity without \"id\" attribute: " + conf);
			return false;
		}
		string id = attr_id.value();
		Entity e = EntityFactory::build(el);
		if (NullEntity.equals(e)) {
			_onConfigError("Failed to build Entity \"" + id + "\": " + conf);
			return false;
		}
		_cache[id] = e;

		el = el.next_sibling("entity");
	}

	return true;
}

Entity EntityStore::get(string id) {
	if (_cache.find(id) == _cache.end()) {
		_logger.error("Entity \"", id, "\" not available");
		return NullEntity;
	}
	return _cache[id];
}
