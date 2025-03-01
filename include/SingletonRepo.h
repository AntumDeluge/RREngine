/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SINGLETON_REPO_H
#define RRE_SINGLETON_REPO_H

#include "FontMapLoader.h"
#include "GameLogic.h"
#include "Input.h"
#include "frame.h"
#include "viewport.h"


static inline FontMapLoader* GetFontMapLoader() { return FontMapLoader::get(); }

static inline GameLogic* GetGameLogic() { return GameLogic::get(); }

static inline GameWindow* GetGameWindow() { return GameWindow::get(); }

static inline Input* GetInput() { return Input::get(); }

static inline ViewPort* GetViewPort() { return ViewPort::get(); }

#endif /* RRE_SINGLETON_REPO_H */
