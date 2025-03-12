/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

//#include <pugixml.hpp>

#include "Dialog.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "factory/EntityFactory.hpp"

//using namespace pugi;
using namespace std;


static Logger _logger = Logger::getLogger("EntityFactory");

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

Entity EntityFactory::getEntity(string id) {
	string entity_conf = Path::rabs("data/conf/entities.xml");
	if (!Filesystem::fexist(entity_conf)) {
		_onConfigError("Entity configuration not found: " + entity_conf);
		return nullptr;
	}

	// pugixml example
//	pugi::xml_document doc;
//	if (doc.load_file(entity_conf.c_str()).status != pugi::status_ok) {
//		_onConfigError("Failed to load entities configuration: " + entity_conf);
//		return nullptr;
//	}
//
//	pugi::xml_node root = doc.document_element().child("entities");
//	if (root.type() == pugi::node_null) {
//		_onConfigError("XML Parsing Error", "Root tag \"entities\" not found: " + entity_conf);
//		return nullptr;
//	}
//
//	pugi::xml_node entity_tag = root.child("entity");
//	while (entity_tag.type() != pugi::node_null) {
//		pugi::xml_attribute id_attr = entity_tag.attribute("id");
//		if (id_attr.empty()) {
//			_onConfigError("XML Parsing Error", "Attribute \"id\" not found: " + entity_conf);
//			return nullptr;
//		} else if (id.compare(id_attr.value()) == 0) {
//			// entity with matching ID found
//			break;
//		}
//
//		entity_tag = entity_tag.next_sibling("entity");
//	}
//
//	if (entity_tag.type() == pugi::node_null) {
//		_onConfigError("Entity \"" + id + "\" not configured: " + entity_conf);
//		return nullptr;
//	}

	Entity entity = Entity::create();

	// TODO:

	return entity;
}
