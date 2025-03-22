/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "GlobalFunctions.hpp"
#include "Logger.hpp"
#include "Player.hpp"
#include "Scene.hpp"
#include "SingletonRepo.hpp"


static Logger _logger = Logger::getLogger("GlobalFunctions");

Player* GetPlayer() {
	Scene* scene = GetViewport()->getScene();
	if (!scene) {
		_logger.warn("Scene not available");
		return nullptr;
	}
	return scene->getPlayer();
}
