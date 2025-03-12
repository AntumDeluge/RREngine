
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GAME_MODE
#define RRE_GAME_MODE


/**
 * Defined game modes enumeration.
 *
 * TODO: rename file to GameMode.hpp
 */
namespace GameMode {
	enum Mode {
		/** Game has not started. */
		NONE,
		/** Intro movie is being played. */
		INTRO,
		/** Title menu is being displayed. */
		TITLE,
		/** Game is in an active scene. */
		SCENE,
		/** Game is in a paused scene. */
		SCENE_PAUSED
	};
};

#endif /* RRE_GAME_MODE */
