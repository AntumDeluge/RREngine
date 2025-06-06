/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_MOVIE
#define RRE_MOVIE

#include <cstdint> // *int*_t
#include <string>
#include <utility> // std::pair
#include <vector>

#include "FontMap.hpp"
#include "Image.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"
#include "Sprite.hpp"


/**
 * Type representing <duration (ms), image>.
 *
 * TODO:
 * - don't use pointers
 * - invert order (<image, duration>) to match sprite animations
 */
typedef std::pair<uint32_t, Image*> MovieFrame;

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
	/** Timestamp of first played frame. */
	uint64_t init_time = 0;

	/** Fade in animation duration in milliseconds. */
	uint32_t fade_in = 0;
	/** Fade out animation duration in milliseconds. */
	uint32_t fade_out = 0;

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

	/**
	 * Retrieves total duration of movie.
	 *
	 * @return
	 *   Movie duration in milliseconds.
	 */
	uint32_t getDuration();

	/** Marks movie for playback. */
	void play() {
		frame_start = 0;
		playing = true;
	}

	/**
	 * Draws current frame onto the renderer.
	 *
	 * @param ctx
	 *   Rendering target context.
	 */
	void render(Renderer* ctx);

	/**
	 * Handles callback when movie finishes.
	 *
	 * FIXME: not necessary?
	 */
	void onComplete();

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

	/**
	 * Sets fade in animation duration.
	 *
	 * TODO: support fade color
	 *
	 * @param ms
	 *   Duration in milliseconds.
	 */
	void setFadeIn(uint32_t ms) { fade_in = ms; }

	/**
	 * Sets fade out animation duration.
	 *
	 * @param ms
	 *   Duration in milliseconds.
	 */
	void setFadeOut(uint32_t ms) { fade_out = ms; }
};

#endif /* RRE_MOVIE */
