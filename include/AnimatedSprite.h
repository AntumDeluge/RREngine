/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_ANIMATED_SPRITE
#define RRE_ANIMATED_SPRITE

#include <cstdint> // uint*_t
#include <string>
//#include <tuple>
#include <unordered_map>
#include <utility> // std::pair
#include <vector>

#include <SDL2/SDL_render.h>

#include "Logger.h"
#include "Sprite.h"
#include "ViewportRenderer.h"


/**
 * Represents a frame of animation with duration indexed by tile index.
 */
typedef std::pair<uint16_t, uint32_t> AnimationFrame;

/**
 * Represents animation frames & durations.
 *
 * FIXME: should a fixed size type be used instead of std::vector?
 */
typedef std::vector<AnimationFrame> Animation;

//typedef std::tuple<std::string, bool, Animation> AnimationMode;
typedef std::pair<bool, Animation*> AnimationMode;

class AnimatedSprite: public Sprite {
private:
	static Logger logger;

	/** All available animation modes of this sprite. */
	std::unordered_map<std::string, AnimationMode*> modes;

	/** Animation currently being displayed. */
	AnimationMode* current_mode;

	std::string default_mode;

	/** Frame currently being drawn. */
	//AnimationFrame* current_frame;
	uint16_t frame_index = 0;
	/** Time when frame animation began. */
	uint32_t frame_start = 0;

public:
	AnimatedSprite(SDL_Texture* texture);
	AnimatedSprite(std::string id);
	AnimatedSprite();

	~AnimatedSprite() {
		for (std::pair<std::string, AnimationMode*> m: this->modes) {
			if (m.second != nullptr) {
				if (m.second->second != nullptr) {
					delete m.second->second;
					m.second->second = nullptr;
				}
				delete m.second;
				m.second = nullptr;
			}
		}
		this->modes.clear();
		this->current_mode = nullptr; // should have been deleted in modes loop
	}

	void addMode(std::string id, bool loop, Animation* animation);

	void setMode(std::string id);

	void setDefaultMode(std::string id) {
		this->default_mode = id;
	}

	/**
	 * Overrides `Sprite.render`
	 */
	void render(ViewportRenderer* viewport, uint16_t x, uint16_t y);

private:
	/**
	 * Checks if current animation should loop playback.
	 */
	bool loops() {
		return this->current_mode->first;
	}

	AnimationMode* getDefaultMode();
};

#endif /* RRE_ANIMATED_SPRITE */
