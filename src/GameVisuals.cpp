/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "GameVisuals.hpp"
#include "SingletonRepo.hpp"
#include "store/SceneStore.hpp"

using namespace std;


Logger GameVisuals::logger = Logger::getLogger("GameVisuals");

// initialize singleton instance
unique_ptr<GameVisuals> GameVisuals::instance = nullptr;
mutex GameVisuals::mtx;

bool GameVisuals::setScene(string id) {
	unsetScene();
	if (id.empty()) {
		// empty string means no scene is to be set
		return true;
	}
	scene = SceneStore::get(id);
	bool result = scene != nullptr;
	if (!result) {
		logger.error("Failed to set scene: ", id);
	}
	return result;
}

void GameVisuals::unsetScene() {
	if (scene) {
		delete scene;
		scene = nullptr;
	}
}

void GameVisuals::renderScene() {
	if (!scene) {
		return;
	}
	scene->render(GetViewport());
}
