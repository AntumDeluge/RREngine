/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <algorithm> // std::find

#include "Scene.hpp"
#include "SingletonRepo.hpp"

using namespace std;


void Scene::render(ViewportRenderer* viewport) {
	for (Entity* entity: this->entities) {
		entity->render(viewport);
	}

	// TODO:
}


void Scene::removeEntity(Entity* entity) {
	auto e_end = this->entities.end();
	auto it = find(this->entities.begin(), e_end, entity);
	if (it != e_end) {
		this->entities.erase(it);
	}
}
