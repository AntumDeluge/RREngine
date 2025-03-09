/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "Movie.h"
#include "Viewport.h"

using namespace std;


Logger Movie::logger = Logger::getLogger("Movie");

void Movie::render(void* viewport) {

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

	// FIXME: ensure instance of Viewport
	((Viewport*) viewport)->drawImage(frame.second, 0, 0);
}
