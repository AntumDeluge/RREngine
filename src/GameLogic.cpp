/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#if RRE_DEBUGGING
//~ #include <string>
#endif

#include "GameLogic.hpp"
#include "SingletonRepo.hpp"
#include "impl/SceneImpl.hpp"

using namespace std;


Logger GameLogic::logger = Logger::getLogger("GameLogic");

// initialize singleton instance to NULL
unique_ptr<GameLogic> GameLogic::instance = nullptr;
mutex GameLogic::mtx;

// default step delay is 300ms
uint32_t GameLogic::step_delay = 300;

#if RRE_DEBUGGING
// for debugging delay between steps
uint64_t prev_step_time = 0;
#endif

void GameLogic::step(uint64_t step_time) {
	this->step_time = step_time;

#if RRE_DEBUGGING
	uint32_t step_diff = this->step_time - prev_step_time;
	//~ this->logger.debug("time since last step: " + std::to_string(step_diff) + "ms");
#endif

	SceneImpl* scene = GetGameVisuals()->getScene();
	if (scene) {
		scene->logic();
	}

	// TODO:

#if RRE_DEBUGGING
	this->prev_step_time = this->step_time;
#endif
}
