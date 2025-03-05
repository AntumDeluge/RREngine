/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

using namespace std;

#include <iostream>
#include <sstream>

#include "Logger.h"
#include "Path.h"


// initialize static members
// TODO: override logger level via command line parameter
#if RRE_DEBUGGING
LogLevel Logger::default_level = DEBUG;
#else
LogLevel Logger::default_level = ERROR;
#endif
unordered_map<string, Logger*> Logger::loggers = {};

Logger::Logger(string id, LogLevel level, string file) {
	this->id = id;
	this->level = level;
	if (file.compare("") == 0) {
		file = Path::join(Path::dir_root, "debug.log");
	}
	this->file = file;

	// TODO: get absolute path of 'file' parameter

	this->debug("Initialized logging to file: \"" + this->file + "\"");
}

void Logger::write(string msg) {
	// TODO: export to file
}

void Logger::log(LogLevel level, string msg) {
	if (this->level < level || this->level == SILENT || level == SILENT) {
		// do nothing
		return;
	}

	ostringstream os;
	switch (level) {
		case WARN:
			os << "WARN:  ";
			break;
		case ERROR:
			os << "ERROR: ";
			break;
		case DEBUG:
			os << "DEBUG: ";
			break;
		default:
			os << "INFO:  ";
	}

	os << "(" << this->id << ") " << msg;

	const string st = os.str();
	if (level == ERROR) {
		cerr << st << endl;
	} else {
		cout << st << endl;
	}
	this->write(st);
}
