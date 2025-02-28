/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_LOGGER_H
#define RRE_LOGGER_H

#include <string>
#include <unordered_map>


enum LogLevel {
	SILENT,
	ERROR,
	WARN,
	INFO,
	DEBUG
};

class Logger {
private:
	std::string id;
	LogLevel level;
	std::string file;

	static LogLevel default_level;

	/** Logger instances. */
	static std::unordered_map<std::string, Logger*> loggers;

	Logger(std::string id, LogLevel level, std::string file);
	Logger(std::string id, LogLevel level) : Logger(id, level, "") {}
	Logger(std::string id, std::string file) : Logger(id, Logger::default_level, file) {}
	Logger(std::string id) : Logger(id, Logger::default_level, "") {}

	void write(std::string msg);

public:
	static Logger* getLogger(std::string id) {
		Logger* logger = nullptr;
		if (Logger::loggers.find(id) != Logger::loggers.end()) {
			logger = Logger::loggers[id];
		} else {
			logger = new Logger(id);
			Logger::loggers[id] = logger;
		}
		return logger;
	}

	void log(LogLevel level, std::string msg);

	void log(std::string msg) {
		this->log(INFO, msg);
	}

	void info(std::string msg) {
		this->log(INFO, msg);
	}

	void warn(std::string msg) {
		this->log(WARN, msg);
	}

	void error(std::string msg) {
		this->log(ERROR, msg);
	}

	void debug(std::string msg) {
		this->log(DEBUG, msg);
	}

	std::string getFile() {
		return this->file;
	}
};

#endif /* RRE_LOGGER_H */
