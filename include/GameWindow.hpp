/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GAME_WINDOW
#define RRE_GAME_WINDOW

#include <memory> // std::unique_ptr, std::make_unique
#include <mutex>
#include <string>

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_video.h>

#include "Logger.hpp"
#include "Viewport.hpp"


/**
 * Manages the window frame.
 */
class GameWindow {
private:
	/** Logger instance. */
	// TODO: make static
	Logger logger;

	/** Static singleton instance. */
	static std::unique_ptr<GameWindow> instance;
	/** Mutex for thread safety. */
	static std::mutex mtx;

	// delete copy constructor & assignment operator for singleton
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;

	/** Text displayed in window title bar. */
	std::string title;

	/** The system window instance. */
	SDL_Window* window;

	/**
	 * Renderer where images are drawn.
	 *
	 * TODO: use abstract `ViewportRender`
	 */
	Viewport* viewport;

	/** Active music. */
	Mix_Music* music;

	/** Game loop iterator flag. */
	bool quit;

public:
	/** Default constructor. */
	GameWindow();

	/** Default destructor. */
	~GameWindow() {}

	/**
	 * Initializes & retrieves singleton instance.
	 *
	 * @return
	 *   Static singleton instance.
	 */
	static GameWindow* get() {
		if (!instance) {
			std::lock_guard<std::mutex> lock(mtx); // lock for thread safety
			instance = std::make_unique<GameWindow>();
		}
		return instance.get();
	}

	/**
	 * Sets window title bar text.
	 *
	 * @param title
	 *   New title text.
	 */
	void setTitle(const std::string title);

	/**
	 * Initializes systems.
	 *
	 * @param title
	 *   Window title bar text.
	 * @param width
	 *   Window pixel width.
	 * @param height
	 *   Window pixel height.
	 * @return
	 *   Return code. 0 if completed without errors.
	 */
	int init(const std::string title, const int width, const int height);

	/**
	 * Initializes systems with default window title.
	 *
	 * @param width
	 *   Window pixel width.
	 * @param height
	 *   Window pixel height.
	 * @return
	 *   Return code. 0 if completed without errors.
	 */
	int init(const int width, const int height) {
		return this->init(this->title, width, height);
	}
	/** Marks game loop for ending & shutting down cleanly. */
	void endGameLoop();

	/** Cleans up initialized systems. */
	void shutdown();

	/**
	 * Retrieves the system window.
	 *
	 * @return
	 *   `SDL_Window` instance.
	 */
	SDL_Window* getElement() {
		if (this->window == nullptr) {
			this->logger.warn("Returning SDL_Window before initialization");
		}
		return this->window;
	}

	/**
	 * Retrieves the drawing renderer.
	 *
	 * TODO: use abstract `ViewportRenderer`
	 *
	 * @return
	 *   Viewport renderer instance.
	 */
	Viewport* getViewport() { return this->viewport; }

	/**
	 * Sets music to play.
	 *
	 * @param id
	 *   Music identifier.
	 */
	void playMusic(std::string id);

	/** Stops music currently playing. */
	void stopMusic();
};

#endif /* RRE_GAME_WINDOW */
