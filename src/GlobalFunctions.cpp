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
#include "enum/MomentumDir.hpp"


static Logger _logger = Logger::getLogger("GlobalFunctions");

Player* GetPlayer() {
	SceneImpl* scene = GetGameVisuals()->getScene();
	if (!scene) {
		_logger.warn("Scene not available");
		return nullptr;
	}
	return dynamic_cast<Scene*>(scene)->getPlayer();
}

uint8_t GetPlayerDirection() {
	Player* player = GetPlayer();
	if (!player) {
		_logger.warn("Player not available");
		return MomentumDir::NONE;
	}

	return player->getDirection();
}

uint8_t AddPlayerDirection(uint8_t dir) {
	Player* player = GetPlayer();
	if (!player) {
		_logger.warn("Player not available");
		return MomentumDir::NONE;
	}

	return player->addDirection(dir);
}

uint8_t RemovePlayerDirection(uint8_t dir) {
	Player* player = GetPlayer();
	if (!player) {
		_logger.warn("Player not available");
		return MomentumDir::NONE;
	}

	return player->removeDirection(dir);
}
