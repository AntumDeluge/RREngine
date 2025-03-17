/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include "FadeEffect.hpp"


FadeEffect::FadeEffect(uint32_t f_time)
: viewport(GetViewport()), f_time(f_time), step_rate(f_time / 256) {
	SDL_GetRenderDrawColor(viewport->getRenderer(), &f_color.r, &f_color.g, &f_color.b, nullptr);
}

void FadeEffect::stepFadeIn() {
	uint64_t draw_time = SDL_GetTicks64();
	if (start_time == 0) {
		start_time = draw_time;
	}
}

void FadeEffect::stepFadeOut() {
	uint64_t draw_time = SDL_GetTicks64();
	if (start_time == 0) {
		start_time = draw_time;
	}
}
