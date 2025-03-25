/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GAME_VISUALS
#define RRE_GAME_VISUALS

#include <memory> // std::unique_ptr, std::make_unique
#include <mutex>

#include "Logger.hpp"


class GameVisuals {
private:
	/** Logger instance for this class. */
	static Logger logger;

	/** Static singleton instance. */
	static std::unique_ptr<GameVisuals> instance;
	/** Mutex for thread safety. */
	static std::mutex mtx;

	// delete copy constructor & assignment operator for singleton
	GameVisuals(const GameVisuals&) = delete;
	GameVisuals& operator=(const GameVisuals&) = delete;

	public:
	/** Default constructor. */
	GameVisuals() {}

	/**
	 * Default destructor.
	 */
	~GameVisuals() {}

	/**
	 * Initializes & retrieves singleton instance.
	 *
	 * @return
	 *   Static singleton instance.
	 */
	static GameVisuals* get() {
		if (!instance) {
			std::lock_guard<std::mutex> lock(mtx); // lock for thread safety
			instance = std::make_unique<GameVisuals>();
		}
		return instance.get();
	}
};

#endif /* RRE_GAME_VISUALS */
