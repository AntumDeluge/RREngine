/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <SDL2/SDL_render.h>

#include "Scene.h"
#include "SingletonRepo.h"


void Scene::render() {
	SDL_Renderer* renderer = GetViewport()->getRenderer();

	// TODO:
}
