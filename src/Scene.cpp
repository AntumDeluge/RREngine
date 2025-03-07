/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

using namespace std;

#include <SDL2/SDL_render.h>

#include "Scene.h"
#include "SingletonRepo.h"


void Scene::renderBackground(string data) {
	SDL_Renderer* renderer = GetViewport()->getRenderer();

	// TODO:
}

void Scene::renderTerrain(string data) {
	SDL_Renderer* renderer = GetViewport()->getRenderer();

	// TODO:
}

void Scene::renderForeground(string data) {
	SDL_Renderer* renderer = GetViewport()->getRenderer();

	// TODO:
}
