/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SCENE_IMPL
#define RRE_SCENE_IMPL

#include "ViewportRenderer.hpp"


class SceneImpl {
public:
	/** Virtual default destructor. */
	virtual ~SceneImpl() {}

	virtual void logic() = 0;

	virtual void render(ViewportRenderer* viewport) = 0;
};
#endif /* RRE_SCENE_IMPL */
