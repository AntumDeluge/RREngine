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

#include "FontMap.h"
#include "ImageImpl.h"
#include "Logger.h"
#include "Sprite.h"


/** Type representing <duration (ms), image>. */
typedef std::pair<uint32_t, ImageImpl*> MovieFrame;
typedef std::vector<MovieFrame> MovieFrameList;

class Movie {
private:
	static Logger logger;

	MovieFrameList frames;
	std::vector<Sprite*> text_sprites;

	/** Index of frame to be drawn. */
	uint16_t frame_index = 0;
	/** Time at which frame drawing initiated. */
	uint32_t frame_start = 0;
	/** Denotes frames can be drawn. */
	bool playing = false;

public:
	// default constructor
	Movie() {}
	Movie(MovieFrameList frames) { this->frames = frames; }
	~Movie() {
		this->clearText();
		for (MovieFrame f: this->frames) {
			delete f.second;
		}
		this->frames.clear();
	}

	void play() {
		this->frame_start = SDL_GetTicks64();
		this->playing = true;
	}

	void render(void* viewport);

	void onComplete() {
#if RRE_DEBUGGING
		this->logger.debug("Movie has ended");
#endif

		// TODO: execute callback to notify thread that movie has finished
	}

	bool ended() {
		return !this->playing;
	}

	void addText(FontMap* font_map, uint32_t expires, std::string text);
	void addText(FontMap* font_map, std::string text);
	void addText(uint32_t expires, std::string text);
	void addText(std::string text);

	void clearText() {
		for (Sprite* s: this->text_sprites) {
			delete s;
		}
		this->text_sprites.clear();
	}
};

#endif /* RRE_MOVIE */
