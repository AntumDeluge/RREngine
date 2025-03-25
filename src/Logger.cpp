/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include "Logger.hpp"
#include "Path.hpp"

using namespace std;


// initialize static members
// TODO: override logger level via command line parameter
#if RRE_DEBUGGING
LogLevel Logger::default_level = DEBUG;
#else
LogLevel Logger::default_level = ERROR;
#endif
bool Logger::verbose = false;

Logger::Logger(string id, LogLevel level, string file) {
	this->id = id;
	this->level = level;
	if (file.compare("") == 0) {
		file = Path::join(Path::dir_root, "debug.log");
	}
	this->file = file;

	// TODO: get absolute path of 'file' parameter

#if RRE_DEBUGGING
	if (Logger::verbose) {
		this->debug("Initialized logging to file: \"" + this->file + "\"");
	}
#endif
}

void Logger::setVerbose(bool verbose) {
	Logger::verbose = verbose;
#if RRE_DEBUGGING
	Logger::getLogger("Logger").debug("Verbose output "
			+ string(Logger::verbose ? "enabled" : "disabled"));
#endif
}

void Logger::write(string msg) {
	// TODO: export to file
}
