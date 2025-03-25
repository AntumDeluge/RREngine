/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "Movie.hpp"
#include "SingletonRepo.hpp"
#include "reso.hpp"
#include "store/FontMapStore.hpp"

using namespace std;


Logger Movie::logger = Logger::getLogger("Movie");

void Movie::render(ViewportImpl* viewport) {

	uint16_t frames_count = this->frames.size();
	if (!this->playing || frames_count == 0) {
		return;
	}

	uint32_t render_time = SDL_GetTicks64();

	MovieFrame frame = this->frames[this->frame_index]; // @suppress("Invalid arguments")

	if (render_time - this->frame_start > frame.first) {
		this->frame_index++;

		if (this->frame_index >= frames_count) {
			// movie has finished
			this->playing = false;
			this->onComplete();
			return;
		}

		this->frame_start = render_time;
		frame = this->frames[this->frame_index];
	}

	viewport->drawImage(frame.second, 0, 0);

	uint16_t y_offset = 0;
	for (Sprite* s: this->text_sprites) {
		uint16_t s_height = s->getHeight();
		// TODO: need sprite class that defines text position
		uint16_t center_x = (RES1.first / 2) - (s->getWidth() / 2);
		uint16_t center_y = (RES1.second / 2) - (s_height / 2);
		viewport->drawImage(s, center_x, center_y + y_offset);

		y_offset += s_height + 1;
	}
}

void Movie::addText(FontMap* font_map, uint32_t expires, string text) {
	Sprite* sprite = FontMapStore::buildTextSprite(font_map, text);
	sprite->setExpiration(expires);
	this->text_sprites.push_back(sprite);
}

void Movie::addText(FontMap* font_map, string text) {
	this->text_sprites.push_back(FontMapStore::buildTextSprite(font_map, text));
}

void Movie::addText(uint32_t expires, string text) {
	this->addText(GetViewport()->getFontMap(), expires, text);
}

void Movie::addText(string text) {
	this->addText(GetViewport()->getFontMap(), text);
}
