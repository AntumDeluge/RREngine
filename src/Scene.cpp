/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <algorithm> // std::find

#include "Scene.hpp"
#include "SingletonRepo.hpp"

using namespace std;


Logger Scene::logger = Logger::getLogger("Scene");

void Scene::render(ViewportRenderer* viewport) {
	for (Object* obj: this->objects) {
		obj->render(viewport);
	}

	// TODO:
}


void Scene::addObject(Object* obj) {
	obj->setId(next_object_id);
	objects.push_back(obj);
	// increment for next object to be added
	next_object_id++;
	obj->onAdded(this);
}

void Scene::removeObject(Object* obj) {
	auto e_end = this->objects.end();
	auto it = find(this->objects.begin(), e_end, obj);
	if (it != e_end) {
		this->objects.erase(it);
	}
}
