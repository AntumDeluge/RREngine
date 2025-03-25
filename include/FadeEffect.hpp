/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FADE_EFFECT
#define RRE_FADE_EFFECT

#include <cstdint> // *int*_t

#include <SDL2/SDL_pixels.h>

#include "SingletonRepo.hpp"
#include "impl/ViewportImpl.hpp"


class FadeEffect {
private:
	ViewportImpl* viewport;
	uint32_t f_time;
	SDL_Color f_color;

	uint64_t start_time = 0;
	uint32_t step_rate;
	uint8_t alpha = 0;

public:
	FadeEffect(uint32_t f_time, SDL_Color f_color)
	: viewport(GetViewport()), f_time(f_time), f_color(f_color), step_rate(f_time / 256) {}

	FadeEffect(uint32_t f_time);

	void stepFadeIn();

	void stepFadeOut();
};

#endif /* RRE_FADE_EFFECT */
