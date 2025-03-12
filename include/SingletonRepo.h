/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SINGLETON_REPO_H
#define RRE_SINGLETON_REPO_H

#include "GameLogic.h"
#include "GameWindow.h"
#include "Input.h"
#include "Viewport.h"


/**
 * Retrieves game logic singleton.
 *
 * @return
 *   `GameLogic` singleton instance.
 */
static inline GameLogic* GetGameLogic() { return GameLogic::get(); }

/**
 * Retrieves game window singleton.
 *
 * @return
 *   `GameWindow` singleton instance.
 */
static inline GameWindow* GetGameWindow() { return GameWindow::get(); }

/**
 * Retrieves input singleton.
 *
 * @return
 *   `Input` singleton instance.
 */
static inline Input* GetInput() { return Input::get(); }

/**
 * Retrieves viewport renderer singleton.
 *
 * @return
 *   `Viewport` singleton instance.
 */
static inline Viewport* GetViewport() { return Viewport::get(); }

#endif /* RRE_SINGLETON_REPO_H */
