/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "Dialog.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "Sprite.hpp"
#include "factory/EntityFactory.hpp"
#include "store/SpriteStore.hpp"

using namespace std;
using namespace tinyxml2;


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

Entity EntityFactory::build(XMLElement* el) {
	Entity entity;

	Sprite* sprite = nullptr;
	const XMLAttribute* attr_sprite = el->FindAttribute("sprite");
	if (!attr_sprite) {
		_logger.warn("Entity sprite not configured");
	} else {
		sprite = SpriteStore::get(attr_sprite->Value());
	}

	uint32_t width = 0, height = 0;
	const XMLAttribute* attr_width = el->FindAttribute("width");
	if (attr_width != nullptr) {
		width = attr_width->UnsignedValue();
	}
	const XMLAttribute* attr_height = el->FindAttribute("height");
	if (attr_height != nullptr) {
		height = attr_height->UnsignedValue();
	}

	if (width == 0 or height == 0) {
		_logger.warn("Entity dimensions not configured correctly; falling back to sprite dimensions");
		entity = Entity(sprite);
	} else {
		entity = Entity(sprite, width, height);
	}

	float momentum = 0;
	XMLElement* el_momentum = el->FirstChildElement("momentum");
	if (el_momentum) {
		momentum = el_momentum->FloatText();
	}
	entity.set("base_momentum", momentum);

	// TODO: other entity attributes.

	return entity;
}
