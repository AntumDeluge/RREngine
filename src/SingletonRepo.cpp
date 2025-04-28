/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "SingletonRepo.hpp"
#include "Viewport.hpp"


Renderer* GetRenderer() {
	return Viewport::get()->getRenderer();
}

ViewportImpl* GetViewport() {
	return Viewport::get();
}
