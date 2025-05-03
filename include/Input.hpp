/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_INPUT
#define RRE_INPUT

#include <cstdint> // *int*_t
#include <memory> // std::unique_ptr, std::make_unique
#include <mutex>
#include <string>
#include <utility> // std::pair
#include <vector>

#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>

#include "Logger.hpp"


/**
 * Manages user input.
 *
 * TODO:
 * - _maybe_ convert to namespace
 * - listen for game controller connect/disconnect
 * - map game controller input
 */
class Input {
private:
	static Logger logger;

	/** Active gamepad/joystick. */
	SDL_GameController* gamepad;

	/** Detected gamepads/joysticks listed by <index, GUID>. */
	std::vector<std::pair<int32_t, SDL_JoystickGUID>> gamepad_guids;

	/** List of keyboard keys currently depressed. */
	std::vector<SDL_Keycode> pressed_keys;

	/** Static singleton instance. */
	static std::unique_ptr<Input> instance;
	/** Mutex for thread safety. */
	static std::mutex mtx;

	// delete copy constructor & assignment operator for singleton
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

	// default configuration (keyboard)
	SDL_KeyCode up = SDLK_UP;
	SDL_KeyCode down = SDLK_DOWN;
	SDL_KeyCode left = SDLK_LEFT;
	SDL_KeyCode right = SDLK_RIGHT;
	SDL_KeyCode fire = SDLK_a;
	SDL_KeyCode jump = SDLK_s;
	SDL_KeyCode cycle_w_next = SDLK_GREATER;
	SDL_KeyCode cycle_w_prev = SDLK_LESS;
	SDL_KeyCode menu = SDLK_ESCAPE;

	/**
	 * Checks if a key is depressed.
	 *
	 * @param key
	 *   Keycode to check.
	 * @return
	 *   `true` if found in pressed keys vector.
	 */
	bool keyIsPressed(SDL_Keycode key);

	/**
	 * Checks if a key is considered a direction press.
	 *
	 * @param key
	 *   Keycode to check.
	 * @return
	 *   `true` if key is "left", "right", "up", or "down".
	 */
	bool keyIsDirection(SDL_Keycode key);

	/**
	 * Simulates releasing a keyboard key.
	 *
	 * NOTE: experimental, unused
	 *
	 * @param key
	 *   Keycode of key to be released.
	 * @param mod
	 *   Optional modifier.
	 */
	void releaseKey(SDL_Keycode key, uint16_t mod=KMOD_NONE);

public:
	/** Default constructor. */
	Input();

	/** Default destructor. */
	~Input() {
		if (gamepad != nullptr) {
			SDL_GameControllerClose(gamepad);
			gamepad = nullptr;
		}
	}

	/**
	 * Initializes & retrieves singleton instance.
	 *
	 * @return
	 *   Static singleton instance.
	 */
	static Input* get() {
		if (!instance) {
			std::lock_guard<std::mutex> lock(mtx); // lock for thread safety
			instance = std::make_unique<Input>();
		}
		return instance.get();
	}

	/**
	 * Sets the active gamepad/joystick.
	 *
	 * @param guid
	 *   Device's global ID.
	 */
	bool setGamepad(SDL_JoystickGUID guid);

	/**
	 * Sets the active gamepad/joystick.
	 *
	 * @param idx
	 *   Device's system index.
	 */
	bool setGamepad(int32_t idx);

	/**
	 * Retrieves an attached gamepad/joystick.
	 *
	 * NOTE: Receiving function must call `SDL_GameControllerClose` on returned device.
	 *
	 * @param guid
	 *   Device's global ID.
	 * @return
	 *   Game controller instance or `null`.
	 */
	SDL_GameController* getGamepad(SDL_JoystickGUID guid);

	/**
	 * Retrieves gamepad/joystick device name.
	 *
	 * @param dev
	 *   Device instance.
	 * @return
	 *   Device name.
	 */
	std::string getGamepadName(SDL_GameController* dev);

	/** Refreshes list of detected gamepads/joysticks. */
	void updateGamepads();

	/**
	 * Interprets keyboard key down events.
	 *
	 * @param key
	 *   Depressed key.
	 */
	void onKeyDown(SDL_Keysym key);

	/**
	 * Interprets keyboard key up events.
	 *
	 * @param key
	 *   Released key.
	 */
	void onKeyUp(SDL_Keysym key);
};

#endif /* RRE_INPUT */
