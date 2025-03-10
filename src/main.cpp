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

#include "cxxopts.hpp"

#include "DataLoader.h"
#include "GameConfig.h"
#include "GameLoop.h"
#include "GameWindow.h"
#include "Logger.h"
#include "Path.h"
#include "StrUtil.h"
#include "reso.h"


namespace RRE {
	cxxopts::Options options(Path::getExecutable(true, false));

	void printVersion();
	void printUsage(bool header);
	void exitWithError(int code, string msg, bool show_usage);
	void exitWithError(int code, string msg) { exitWithError(code, msg, false); }
	void populateOptions();
};

int main(int argc, char** argv) {
	// parse command line parameters
	RRE::populateOptions();
	cxxopts::ParseResult args;
	try {
		args = RRE::options.parse(argc, argv);
	} catch (cxxopts::exceptions::parsing& e) {
		RRE::exitWithError(1, e.what(), true);
	}

	if (args.count("help")) {
		RRE::printUsage(true);
		return 0;
	}
	if (args.count("version")) {
		RRE::printVersion();
		return 0;
	}
	if (args.count("verbose")) {
		Logger::setVerbose();
	}

	Logger logger = Logger::getLogger("main");

#if RRE_DEBUGGING
	logger.debug("Compiled using C++ standard: " + to_string(__cplusplus));
#endif

	// change to executable directory
	Path::changeDir(Path::dir_root);

	// TODO: move SDL initialization to here so configuration can be loaded before window is displayed

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
	logger.debug("Game title: " + GameConfig::getTitle());
	logger.debug("Window scale: " + to_string(GameConfig::getScale()));
#endif

	result = win->init(width, height);
	if (result != 0) {
		return result;
	}

	if (scale > 1) {
		win->getViewport()->setScale(scale);
	}

	// renderer must be constructed before texture data can be loaded
	if (!DataLoader::load()) {
		logger.error("Failed to load game data");
#if RRE_DEBUGGING
	} else {
		logger.debug("Game data loaded");
#endif
	}

	GameLoop::start();

	GameWindow::destroy();
	return 0;
}

void RRE::exitWithError(int code, string msg, bool show_usage) {
	cout << endl;
	Logger::getLogger("main").error(msg);
	if (show_usage) RRE::printUsage(false);
	exit(code);
}

void RRE::printUsage(bool header) {
	if (header) {
	cout << endl;
		cout << "R&R Engine: 2D platform game engine" << endl;
	}
	cout << RRE::options.help() << endl;
}

void RRE::printVersion() {
	cout << "R&R Engine version " << RRE_VERSION
#if defined(__clang__)
			<< " (built with Clang " << StrUtil::trim(__clang_version__) << ")"
#elif defined(__GNUC__)
			<< " (built with GNU " << StrUtil::trim(__VERSION__) << ")"
#elif defined(_MSC_VER)
			<< " (built with MSVC " << _MSC_VER / 100 << "." << _MSC_VER % 100 << ")"
#endif
			<< endl;
}

void RRE::populateOptions() {
	RRE::options.add_options()
		("h,help", "Show this help information.")
		("v,version", "Show version information")
		("V,verbose", "Enable verbose logging.")
	;
}
