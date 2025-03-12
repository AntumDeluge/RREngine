/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "Logger.h"
#include "store/EntityStore.hpp"

using namespace std;


static Logger _logger = Logger::getLogger("EntityStore");

bool EntityStore::load() {
	// TODO:

	return true;
}

Entity EntityStore::getEntity(string id) {
	Entity entity = Entity::create();

	// TODO:

	return entity;
}
