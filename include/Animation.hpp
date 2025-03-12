/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_ANIMATION
#define RRE_ANIMATION

#include <cstdint> // *int*_t
#include <utility>
#include <vector>

#include <SDL2/SDL_timer.h>


/**
 * Represents a frame of animation with duration indexed by tile index.
 *
 * First value represents image index, second represents duration.
 */
typedef std::pair<uint32_t, uint32_t> AnimationFrame;

/**
 * Represents a set of animation frames.
 */
typedef std::vector<AnimationFrame> AnimationFrameSet;

/**
 * Animation definition.
 */
struct Animation {
private:
	/** Index of animation frame to be drawn. */
	uint32_t index = 0;
	/** Timestamp of when to step to next animation frame. */
	uint64_t expires = 0;

	/** Configured animation frames. */
	const AnimationFrameSet frames;

public:
	/** Flag denoting if animation should loop after completions. */
	const bool loop;

	/**
	 * Constructs a new animation.
	 *
	 * @param loop
	 *   Whether the animation should loop.
	 * @param frames
	 *   Configured animation frames.
	 */
	Animation(bool loop, AnimationFrameSet frames) {
		this->frames = frames;
		this->loop = loop;
	}

	/**
	 * Constructs a looping animation.
	 *
	 * @param frames
	 *   Configured animation frames.
	 */
	Animation(AnimationFrameSet frames): Animation(true, frames) {}

	/**
	 * Constructs an "uninitialized" animation without any frames.
	 */
	Animation() {
		this->loop = false;
	}

	/**
	 * Checks if animation is ready.
	 *
	 * @return
	 *   `true` if at least one frame is configured.
	 */
	bool ready() {
		return frames.size() > 0;
	}

	/**
	 * Retrieves the index of sprite texture that should be drawn.
	 *
	 * @return
	 *   Texture index of the current frame to be drawn.
	 */
	uint32_t current() {
		if (expires == 0) {
			// animation hasn't started yet
			expires = SDL_GetTicks() + frames[index].second; // @suppress("Field cannot be resolved")
		}

		if (expired()) {
			if (index + 1 < frames.size()) {
				// cycle to next frame
				index++;
			} else {
				// cycle back to first frame
				index = 0;
			}
			// reset expiration for new frame
			expires = SDL_GetTicks() + frames[index].second; // @suppress("Field cannot be resolved")
		}
		return frames[index].first; // @suppress("Field cannot be resolved")
	}

private:
	/**
	 * Checks if current frame has expired.
	 *
	 * @return
	 *   `false` to continue drawing current frame. `true` to move to next frame.
	 */
	bool expired() {
		return SDL_GetTicks64() >= expires;
	}
};

#endif /* RRE_ANIMATION */
