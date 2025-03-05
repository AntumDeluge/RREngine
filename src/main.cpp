/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 *
 * WARNING: This software is in planning stages & is not ready
 * for regular use.
 */

#include "config.h"

#include <cstdint> // uint*_t
#include <iostream>
#include <string>

using namespace std;

#include "DataLoader.h"
#include "GameConfig.h"
#include "GameLoop.h"
#include "GameWindow.h"
#include "Logger.h"
#include "Path.h"
#include "reso.h"


namespace RRE {
	void printVersion();
	void printUsage();
};

int main(int argc, char** argv) {
	Logger* logger = Logger::getLogger("main");

#if RRE_DEBUGGING
	logger->debug("Compiled using C++ standard: " + to_string(__cplusplus));
#endif

	// TODO: parse command line parameters

	// change to executable directory
	Path::changeDir(Path::dir_root);

	// TODO: move SDL initialization to here so configuration can be loaded before window is displayed

	if (!DataLoader::load()) {
		logger->error("Failed to load game data");
#if RRE_DEBUGGING
	} else {
		logger->debug("Game data loaded");
#endif
	}

	GameWindow* win = GameWindow::get();

	int result = GameConfig::load();
	if (result != 0) {
		// FIXME: need to create SDL window to show configuration errors
		return result;
	}

	win->setTitle(GameConfig::getTitle());

	uint16_t scale = GameConfig::getScale();
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

	if (scale > 1) {
		win->getViewport()->setScale(scale);
	}

	GameLoop::setMode(GameMode::TITLE);
	GameLoop::start();

	win->shutdown();
	return 0;
}

void RRE::printUsage() {
	cout << "Usage: TODO" << endl;
}

void RRE::printVersion() {
	cout << "R&R Engine version " << RRE_VERSION << endl;
}
