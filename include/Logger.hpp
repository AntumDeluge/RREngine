/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_LOGGER
#define RRE_LOGGER

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "StrUtil.hpp"


/** Defined logging levels. */
enum LogLevel {
	/** Don't output any messages (least verbose). */
	SILENT,
	/** Output messages up to "error" urgency level. */
	ERROR,
	/** Output messages up to "warning" urgency level. */
	WARN,
	/** Output messages up to "info" urgency level. */
	INFO,
	/** Output messages up to "debug" urgency level (most verbose). */
	DEBUG
};

/**
 * Handles logging messages.
 */
class Logger {
private:
	/** Logger identifier. */
	std::string id;
	/** Max urgency level at which to output messages. */
	LogLevel level;
	/** Optional file where to export messages (not yet supported). */
	std::string file;

	/** Default urgency level when a logger is created without specifying level. */
	static LogLevel default_level;
	/** Flag denoting to display extra, non-critical messages. */
	static bool verbose;

	/**
	 * Creates a new logger.
	 *
	 * @param id
	 *   Logger identifier.
	 * @param level
	 *   Max message urgency level.
	 * @param file
	 *   File where to export messages (not yet supported).
	 */
	Logger(std::string id, LogLevel level, std::string file);

	/**
	 * Creates a new logger.
	 *
	 * @param id
	 *   Logger identifier.
	 * @param level
	 *   Max message urgency level.
	 */
	Logger(std::string id, LogLevel level) : Logger(id, level, "") {}

	/**
	 * Creates a new logger.
	 *
	 * @param id
	 *   Logger identifier.
	 * @param file
	 *   File where to export messages (not yet supported).
	 */
	Logger(std::string id, std::string file) : Logger(id, Logger::default_level, file) {}

	/**
	 * Creates a new logger.
	 *
	 * @param id
	 *   Logger identifier.
	 */
	Logger(std::string id) : Logger(id, Logger::default_level, "") {}

	/**
	 * Exports message to configured file (not yet supported).
	 *
	 * @param msg
	 *   Text to export.
	 */
	void write(std::string msg);

public:
	/**
	 * Default constructor.
	 *
	 * FIXME: may need method to check if logger has been properly initialized
	 */
	Logger() {
		this->level = Logger::default_level;
	}

	/**
	 * Initializes a new logger or retrieves cached one from memory.
	 *
	 * @param id
	 *   Logger identifier.
	 * @return
	 *   Logger instance associated with `id`.
	 */
	static Logger& getLogger(std::string id) {
		/** Logger instances. */
		static std::unordered_map<std::string, Logger> loggers;

		if (loggers.find(id) != loggers.end()) {
			return loggers[id];
		}

		Logger logger(id);
		loggers[id] = logger;
		return loggers[id];
	}

	/**
	 * Enable or disable non-critical verbose messages.
	 *
	 * @param verbose
	 *   `true` to enable, `false` to disable.
	 */
	static void setVerbose(bool verbose);

	/**
	 * Enables non-critical verbose messages.
	 */
	static void setVerbose() { Logger::setVerbose(true); }

	/**
	 * Logs a message.
	 *
	 * Defined in header to allow dynamic creation of necessary instances.
	 *
	 * @param level
	 *   Message urgency level.
	 * @param msg
	 *   Text to output.
	 * @param rem
	 *   Any additional text to append to message.
	 */
	template <typename... vargs>
	void log(LogLevel level, std::string msg, vargs... rem) {
		if (this->level < level || this->level == SILENT || level == SILENT) {
			// do nothing
			return;
		}

		std::ostringstream os;
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

		os << "(" << id << ") " << msg;

		// append remaining messages
		((os << StrUtil::check(rem)), ...);

		const std::string st = os.str();
		if (level == ERROR) {
			std::cerr << st << std::endl;
		} else {
			std::cout << st << std::endl;
		}
		write(st);
	}

	/**
	 * Logs a message at "info" urgency level.
	 *
	 * @param msg
	 *   Text to output.
	 * @param rem
	 *   Any additional text to append to message.
	 */
	template <typename... vargs>
	void log(std::string msg, vargs... rem) {
		this->log(INFO, msg, rem...);
	}

	/**
	 * Logs a message at "info" urgency level.
	 *
	 * @param msg
	 *   Text to output.
	 * @param rem
	 *   Any additional text to append to message.
	 */
	template <typename... vargs>
	void info(std::string msg, vargs... rem) {
		this->log(INFO, msg, rem...);
	}

	/**
	 * Logs a message at "warning" urgency level.
	 *
	 * @param msg
	 *   Text to output.
	 * @param rem
	 *   Any additional text to append to message.
	 */
	template <typename... vargs>
	void warn(std::string msg, vargs... rem) {
		this->log(WARN, msg, rem...);
	}

	/**
	 * Logs a message at "error" urgency level.
	 *
	 * @param msg
	 *   Text to output.
	 * @param rem
	 *   Any additional text to append to message.
	 */
	template <typename... vargs>
	void error(std::string msg, vargs... rem) {
		this->log(ERROR, msg, rem...);
	}

	/**
	 * Logs a message at "debug" urgency level.
	 *
	 * @parm msg
	 *   Text to output.
	 * @param rem
	 *   Any additional text to append to message.
	 */
	template <typename... vargs>
	void debug(std::string msg, vargs... rem) {
		this->log(DEBUG, msg, rem...);
	}

	/**
	 * Retrieves path for exporting messages to file.
	 *
	 * @return
	 *   Absolute file path.
	 */
	std::string getFile() {
		return this->file;
	}
};

#endif /* RRE_LOGGER */
