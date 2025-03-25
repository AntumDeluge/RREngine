/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GAME_VISUALS
#define RRE_GAME_VISUALS

#include <memory> // std::unique_ptr, std::make_unique
#include <mutex>
#include <string>

#include "Logger.hpp"
#include "impl/SceneImpl.hpp"


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

	/** Scene rendered during `GameMode::SCENE`. */
	SceneImpl* scene;

public:
	/** Default constructor. */
	GameVisuals() {
		scene = nullptr;
	}

	/**
	 * Default destructor.
	 */
	~GameVisuals() {
		unsetScene();
	}

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

	/**
	 * Sets current scene data.
	 *
	 * @param id
	 *   Scene identifier.
	 * @return
	 *   `true` if scene was set.
	 */
	bool setScene(std::string id);

	/** Unsets scene data. */
	void unsetScene();

	/**
	 * Retrieves current scene.
	 *
	 * @return
	 *   Active scene instance.
	 */
	SceneImpl* getScene() { return scene; }

	/** Renders current scene on viewport. */
	void renderScene();
};

#endif /* RRE_GAME_VISUALS */
