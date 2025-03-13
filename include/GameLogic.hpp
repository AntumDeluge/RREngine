/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GAME_LOGIC_H
#define RRE_GAME_LOGIC_H

#include <cstdint> // *int*_t
#include <memory> // std::unique_ptr, std::make_unique
#include <mutex>

#include "Logger.hpp"


/**
 * Singleton class to handle game stepping.
 *
 * TODO:
 * - _maybe_ change to namespace
 */
class GameLogic {
private:
	// TODO: make static
	Logger logger;

	/**
	 * Delay (in milliseconds) for each step.
	 *
	 * Default is 300ms.
	 *
	 * FIXME: doesn't need to be static in singleton.
	 */
	static uint32_t step_delay;

	/** Time (in milliseconds) of previous step. */
	uint64_t prev_step_time;
	/** Time (in milliseconds) of current step. */
	uint64_t step_time;

	/** Static singleton instance. */
	static std::unique_ptr<GameLogic> instance;
	/** Mutex for thread safety. */
	static std::mutex mtx;

	// delete copy constructor & assignment operator
	GameLogic(const GameLogic&) = delete;
	GameLogic& operator=(const GameLogic&) = delete;

public:
	/**
	 * Constructs the game logic instance.
	 */
	GameLogic() {
		this->logger = Logger::getLogger("GameLogic");
		this->prev_step_time = 0;
		this->step_time = 0;
	}

	/** Default destructor. */
	~GameLogic() {}

	/**
	 * Initializes & retrieves singleton instance.
	 *
	 * @return
	 *   Static singleton instance.
	 */
	static GameLogic* get() {
		if (!instance) {
			std::lock_guard<std::mutex> lock(mtx); // lock for thread safety
			instance = std::make_unique<GameLogic>();
		}
		return instance.get();
	}

	/**
	 * Executes next game logic step.
	 *
	 * @param step_time
	 *   Time (in milliseconds) since process began.
	 */
	void step(uint64_t step_time);

	/**
	 * Retrieves game logic step delay.
	 *
	 * @return
	 *   Step delay in milliseconds.
	 */
	static uint32_t getStepDelay() {
		return GameLogic::step_delay;
	}

	/**
	 * Sets game logic step delay.
	 *
	 * @param delay
	 *   Step delay in milliseconds.
	 */
	static void setStepDelay(uint32_t delay) {
		GameLogic::step_delay = delay;
	}

	/**
	 * Retrieves time of previous game logic step.
	 *
	 * @return
	 *   Time (in milliseconds) of previous step execution.
	 */
	uint64_t getPrevStepTime() {
		return this->prev_step_time;
	}

	/**
	 * Retrieves time of current game logic step.
	 *
	 * @return
	 *   Time (in milliseconds) of current step execution.
	 */
	uint64_t getStepTime() {
		return this->step_time;
	}
};

#endif /* RRE_GAME_LOGIC_H */
