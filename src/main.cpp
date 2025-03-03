/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 *
 * WARNING: This software is in planning stages & is not ready
 * for regular use.
 */

#include <cstdint> // uint32_t
#include <iostream>
#include <string>

using namespace std;

#if RRE_DEBUGGING
#include "Logger.h"
#endif
#include "GameConfig.h"
#include "GameLoop.h"
#include "GameWindow.h"
#include "config.h"
#include "paths.h"
#include "reso.h"


const string ver = to_string(RREngine_VER_MAJ) + "." + to_string(RREngine_VER_MIN) + "." + to_string(RREngine_VER_REL); // @suppress("Invalid arguments") @suppress("Symbol is not resolved")

void showVersion();

int main(int argc, char** argv) {
#if RRE_DEBUGGING
	Logger* logger = Logger::getLogger("main");
	logger->debug("Compiled using C++ standard: " + to_string(__cplusplus));
#endif

	// TODO: parse command line parameters

	// change to executable directory
	changeDir(dir_root);

	// TODO: move SDL initialization to here so configuration can be loaded before window is displayed

	GameWindow* win = GameWindow::get();

	int result = GameConfig::load();
	if (result != 0) {
		// FIXME: need to create SDL window to show configuration errors
		return result;
	}

	win->setTitle(GameConfig::getTitle());

	uint32_t scale = GameConfig::getScale();
	// initial window dimensions
	int width = RES1.first * scale;
	int height = RES1.second * scale;

#if RRE_DEBUGGING
	logger->debug("Game title: " + GameConfig::getTitle());
	logger->debug("Window scale: " + to_string(GameConfig::getScale()));
#endif

	result = win->init(width, height);
	if (result != 0) {
		return result;
	}

	GameLoop::start();

	win->shutdown();
	return 0;
}


void showVersion() {
	cout << "Version: " << ver << endl;
}
