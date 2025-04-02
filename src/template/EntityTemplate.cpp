/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <cstdint> // *int*_t

#include "template/EntityTemplate.hpp"

using namespace std;


Logger EntityTemplate::logger = Logger::getLogger("EntityTemplate");

EntityTemplate::EntityTemplate() {
	sprite = nullptr;
}

void EntityTemplate::updateAttributes(shared_ptr<Entity> entity) {
	// copy all attributes
	for (auto attr: *this) {
		entity->set(attr.first, attr.second);
	}

	uint32_t width = entity->getUInt("width"), height = entity->getUInt("height");
	if (width == 0 || height == 0) {
		logger.warn("Entity dimensions not configured correctly; falling back to sprite dimensions");
	} else {
		entity->setWidth(width);
		entity->setHeight(height);
	}
}

shared_ptr<Entity> EntityTemplate::build() {
	shared_ptr<Entity> entity = make_shared<Entity>(sprite);
	updateAttributes(entity);
	if (!entity->hasSprite()) {
		logger.warn("Entity sprite not set");
	}
	return entity;
}

shared_ptr<Character> EntityTemplate::buildCharacter() {
	shared_ptr<Character> character = make_shared<Character>(sprite);
	updateAttributes(character);
	if (!character->hasSprite()) {
		logger.warn("Character sprite not set");
	}
	return character;
}

shared_ptr<Player> EntityTemplate::buildPlayer() {
	shared_ptr<Player> player = make_shared<Player>(sprite);
	updateAttributes(player);
	if (!player->hasSprite()) {
		logger.warn("Player sprite not set");
	}
	return player;
}
