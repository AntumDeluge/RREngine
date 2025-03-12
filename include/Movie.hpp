/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_MOVIE
#define RRE_MOVIE

#include "config.h"

#include <cstdint> // uint*_t
#include <string>
#include <utility> // std::pair
#include <vector>

#include <SDL2/SDL_timer.h>

#include "FontMap.hpp"
#include "ImageImpl.hpp"
#include "Logger.hpp"
#include "Sprite.hpp"
#include "ViewportRenderer.hpp"


/**
 * Type representing <duration (ms), image>.
 *
 * TODO:
 * - don't use pointers
 * - invert order (<image, duration>) to match sprite animations
 */
typedef std::pair<uint32_t, ImageImpl*> MovieFrame;

/** Type representing a series of movie frames. */
typedef std::vector<MovieFrame> MovieFrameList;

/**
 * A playable movie.
 */
class Movie {
private:
	static Logger logger;

	/** Frames drawn for this movie. */
	MovieFrameList frames;

	/**
	 * Text drawn for this movie.
	 *
	 * TODO: don't use pointers
	 */
	std::vector<Sprite*> text_sprites;

	/** Index of frame to be drawn. */
	uint16_t frame_index = 0;
	/** Time at which frame drawing initiated. */
	uint32_t frame_start = 0;
	/** Denotes frames can be drawn. */
	bool playing = false;

public:
	/** Default constructor. */
	Movie() {}

	/**
	 * Creates a new movie.
	 *
	 * @param frames
	 *   Frames drawn for this movie.
	 */
	Movie(MovieFrameList frames) { this->frames = frames; }

	/** Default destructor. */
	~Movie() {
		this->clearText();
		for (MovieFrame f: this->frames) {
			delete f.second;
		}
		this->frames.clear();
	}

	/** Marks movie for playback. */
	void play() {
		this->frame_start = SDL_GetTicks64();
		this->playing = true;
	}

	/**
	 * Draws current frame onto the renderer.
	 *
	 * @param viewport
	 *   Viewport renderer.
	 */
	void render(ViewportRenderer* viewport);

	/**
	 * Handles callback when movie finishes.
	 *
	 * FIXME: not necessary?
	 */
	void onComplete() {
#if RRE_DEBUGGING
		this->logger.debug("Movie has ended");
#endif

		// TODO: execute callback to notify thread that movie has finished
	}

	/**
	 * Checks if movie has ended playback.
	 *
	 * @return
	 *  `true` if not marked for playback.
	 */
	bool ended() {
		return !this->playing;
	}

	/**
	 * Adds a line of text to be drawn.
	 *
	 * @param font_map
	 *   Font map reference.
	 * @param expires
	 *   When text sprite should be removed.
	 * @param text
	 *   Text representation to draw.
	 */
	void addText(FontMap* font_map, uint32_t expires, std::string text);

	/**
	 * Adds a line of text to be drawn that doesn't expire.
	 *
	 * @param font_map
	 *   Font map reference.
	 * @param text
	 *   Text representation to draw.
	 */
	void addText(FontMap* font_map, std::string text);

	/**
	 * Adds a line of text to be drawn using default text map.
	 *
	 * @param expires
	 *   When text sprite should be removed.
	 * @param text
	 *   Text representation to draw.
	 */
	void addText(uint32_t expires, std::string text);

	/**
	 * Adds a line of text to be drawn using default text map that doesn't expire.
	 *
	 * @param text
	 *   Text representation to draw.
	 */
	void addText(std::string text);

	/** Removes all text. */
	void clearText() {
		for (Sprite* s: this->text_sprites) {
			delete s;
		}
		this->text_sprites.clear();
	}
};

#endif /* RRE_MOVIE */
