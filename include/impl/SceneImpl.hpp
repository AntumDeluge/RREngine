/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SCENE_IMPL
#define RRE_SCENE_IMPL

#include <cstdint> // *int*_t

#include <SDL2/SDL_rect.h>

#include "HashObject.hpp"
#include "impl/ViewportImpl.hpp"


class SceneImpl: public HashObject {
public:
	/** Virtual default destructor. */
	virtual ~SceneImpl() {}

	virtual void logic() = 0;

	virtual void render(ViewportImpl* viewport) = 0;

	/**
	 * Checks for gravity rate at a given point.
	 *
	 * @param x
	 *   Horizontal position.
	 * @param y
	 *   Vertical position.
	 * @return
	 *   Gravity at given position.
	 */
	virtual float getGravity(uint32_t x, uint32_t y) = 0;

	/**
	 * Checks if a rectangle collides against a ground tile.
	 *
	 * @param rect
	 *   Area to check.
	 * @return
	 *   `true` if bottom of rectangle collides with horizontal line in collision map.
	 */
	virtual bool collidesGround(SDL_Rect rect) = 0;

	/**
	 * Checks if a rectangle collides again a wall tile.
	 *
	 * @param dir
	 *   Direction of entity momentum.
	 * @param rect
	 *   Area to check.
	 * @return
	 *   `true` if side of rectangle collides with vertical line in collision map.
	 */
	virtual bool collidesWall(uint8_t dir, SDL_Rect rect) = 0;
};
#endif /* RRE_SCENE_IMPL */
