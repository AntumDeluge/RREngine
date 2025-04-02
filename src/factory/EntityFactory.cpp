/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <memory> // std::shared_ptr

#include "Dialog.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "Sprite.hpp"
#include "StrUtil.hpp"
#include "factory/EntityFactory.hpp"
#include "store/SpriteStore.hpp"

using namespace pugi;
using namespace std;


static Logger _logger = Logger::getLogger("EntityFactory");

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

Entity EntityFactory::build(xml_node el) {
	Entity entity;

	shared_ptr<Sprite> sprite = nullptr;
	xml_attribute attr_sprite = el.attribute("sprite");
	if (attr_sprite.empty()) {
		_logger.warn("Entity sprite not configured");
	} else {
		sprite = SpriteStore::get(attr_sprite.value());
	}

	uint32_t width = 0, height = 0;
	xml_attribute attr_width = el.attribute("width");
	if (!attr_width.empty()) {
		StrUtil::parseUInt(width, attr_width.value());
	}
	xml_attribute attr_height = el.attribute("height");
	if (!attr_height.empty()) {
		StrUtil::parseUInt(height, attr_height.value());
	}

	if (width == 0 or height == 0) {
		_logger.warn("Entity dimensions not configured correctly; falling back to sprite dimensions");
		entity = Entity(sprite);
	} else {
		entity = Entity(sprite, width, height);
	}

	float momentum = 0;
	xml_node el_momentum = el.child("momentum");
	if (el_momentum.type() != node_null) {
		StrUtil::parseFloat(momentum, el_momentum.text().get());
	}
	entity.set("base_momentum", momentum);

	// TODO: other entity attributes.

	return entity;
}
