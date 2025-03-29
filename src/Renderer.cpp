/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <SDL2/SDL_image.h>

#include "Renderer.hpp"
#include "SingletonRepo.hpp"

using namespace std;


Logger Renderer::logger = Logger::getLogger("Renderer");

Renderer::Renderer() {
	internal = SDL_CreateRenderer(GetGameWindow()->getElement(), -1,
			SDL_RENDERER_ACCELERATED);
	setBlendMode(SDL_BLENDMODE_BLEND);
	setDrawColor(0, 0, 0, 0);
	state = nullptr;
}

void Renderer::clear() {
	SDL_RenderClear(internal);
}

void Renderer::present() {
	SDL_RenderPresent(internal);
}

void Renderer::save() {
	// free previously saved state
	clearState();

	// create new saved state
	state = new RendererState();
	SDL_GetRenderDrawColor(internal, &state->color.r, &state->color.g, &state->color.b,
			&state->color.a);
	SDL_GetRenderDrawBlendMode(internal, &state->blend_mode);
}

void Renderer::restore() {
	if (!state) {
		return;
	}
	setBlendMode(state->blend_mode);
	setDrawColor(state->color);

	// free saved state
	clearState();
}

void Renderer::drawRect(SDL_Rect rect) {
	SDL_RenderDrawRect(internal, &rect);
}

void Renderer::drawRect(int32_t x, int32_t y, int32_t width, int32_t height) {
	drawRect({x, y, width, height});
}

void Renderer::fillRect(SDL_Rect rect) {
	SDL_RenderFillRect(internal, &rect);
}

void Renderer::fillRect(int32_t x, int32_t y, int32_t width, int32_t height) {
	fillRect({x, y, width, height});
}

void Renderer::drawTexture(SDL_Texture* texture, SDL_Rect s_rect, SDL_Rect t_rect,
		SDL_RendererFlip flags) {
	if (texture == nullptr) {
		logger.error("Drawing error: undefined texture");
		return;
	}
	SDL_RenderCopyEx(internal, texture, &s_rect, &t_rect, 0, nullptr, flags);
}

void Renderer::drawImage(Image* img, uint32_t sx, uint32_t sy, uint32_t s_width,
		uint32_t s_height, uint32_t x, uint32_t y, SDL_RendererFlip flags) {
	SDL_Rect s_rect;
	s_rect.x = sx;
	s_rect.y = sy;
	s_rect.w = s_width;
	s_rect.h = s_height;

	SDL_Rect t_rect;
	t_rect.x = x;
	t_rect.y = y;
	t_rect.w = s_rect.w;
	t_rect.h = s_rect.h;

	drawTexture(img->getTexture(), s_rect, t_rect, flags);
}

void Renderer::drawImage(Image* img, uint32_t x, uint32_t y, SDL_RendererFlip flags) {
	SDL_Rect s_rect;
	s_rect.x = 0;
	s_rect.y = 0;
	s_rect.w = img->getWidth();
	s_rect.h = img->getHeight();

	// target rectangle used for offset
	SDL_Rect t_rect;
	t_rect.x = x;
	t_rect.y = y;
	t_rect.w = s_rect.w;
	t_rect.h = s_rect.h;

	drawTexture(img->getTexture(), s_rect, t_rect, flags);
}

void Renderer::setScale(uint16_t scale) {
	SDL_RenderSetScale(internal, scale, scale);
}

void Renderer::setBlendMode(SDL_BlendMode blend_mode) {
	SDL_SetRenderDrawBlendMode(internal, blend_mode);
}

void Renderer::setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	SDL_SetRenderDrawColor(internal, r, g, b, a);
}

SDL_Color Renderer::getDrawColor() {
	SDL_Color color;
	SDL_GetRenderDrawColor(internal, &color.r, &color.g, &color.b, &color.a);
	return color;
}

void Renderer::setDrawColor(SDL_Color color) {
	setDrawColor(color.r, color.g, color.b, color.a);
}

SDL_Texture* Renderer::textureFromSurface(SDL_Surface* surface) {
	return SDL_CreateTextureFromSurface(internal, surface);
}

SDL_Texture* Renderer::textureFromPath(string path) {
	return IMG_LoadTexture(internal, path.c_str());
}
