/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <algorithm> // std::find

#include <SDL2/SDL_render.h>

#include "Scene.h"
#include "SingletonRepo.h"

using namespace std;


void Scene::render() {
	SDL_Renderer* renderer = GetViewport()->getRenderer();

	// TODO:
}


void Scene::removeEntity(Entity* entity) {
	auto e_end = this->entities.end();
	auto it = find(this->entities.begin(), e_end, entity);
	if (it != e_end) {
		this->entities.erase(it);
	}
}
