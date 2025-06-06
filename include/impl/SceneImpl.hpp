/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SCENE_IMPL
#define RRE_SCENE_IMPL

#include <cstdint> // *int*_t
#include <string>

#include <SDL2/SDL_rect.h>

#include "HashObject.hpp"
#include "Renderer.hpp"


class SceneImpl: public HashObject {
public:
	/** Virtual default destructor. */
	virtual ~SceneImpl() {}

	virtual void logic() = 0;

	virtual void render(Renderer* ctx) = 0;

	/**
	 * Retreives scene width.
	 *
	 * @return
	 *   Pixel width.
	 */
	virtual uint32_t getWidth() = 0;

	/**
	 * Retrieves scene height.
	 *
	 * @return
	 *   Pixel height.
	 */
	virtual uint32_t getHeight() = 0;

	/**
	 * Sets drawing offset on horizontal axis.
	 *
	 * @param offset
	 *   Horizontal offset.
	 */
	virtual void setOffsetX(int32_t offset) = 0;

	/**
	 * Sets drawing offset on vertical axis.
	 *
	 * @param offset
	 *   Vertical offset.
	 */
	virtual void setOffsetY(int32_t offset) = 0;

	/**
	 * Retrieves drawing offset on horizontal axis.
	 *
	 * @return
	 *   Horizontal offset.
	 */
	virtual int32_t getOffsetX() = 0;

	/**
	 * Retrieves drawing offset on vertical axis.
	 *
	 * @return
	 *   Vertical offset.
	 */
	virtual int32_t getOffsetY() = 0;

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

	/**
	 * Retrieves scene music.
	 *
	 * @return
	 *   Music to play in this scene.
	 */
	virtual std::string getMusic() = 0;
};

#endif /* RRE_SCENE_IMPL */
