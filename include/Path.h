/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_PATH
#define RRE_PATH

#include <string>


/**
 * File & directory path related functions.
 */
namespace Path {

	/**
	 * Extracts file/directory name from a path.
	 *
	 * @param path
	 *   File/Directory path.
	 * @return
	 *   Path stripped of parent directory tree.
	 */
	std::string basename(std::string path);

	/**
	 * Extracts parent directory from a path.
	 *
	 * @param path
	 *   File/Directory path.
	 * @return
	 *   Parent directory tree path.
	 */
	std::string dirname(std::string path);

	/**
	 * Normalizes path node delimiters for current system.
	 *
	 * - Strips duplicate node delimiters.
	 * - Replaces instances of "/" with "\\" on Win32 platforms.
	 * - Replaces instances of "\\" with "/" on other platforms.
	 *
	 * @param input
	 *   Path to be normalized.
	 * @return
	 *   Path stripped of duplicate node delimiters & formatted for current system.
	 */
	std::string norm(std::string input);

	/**
	 * Normalizes path node delimiters for current system.
	 *
	 * FIXME: this is likely redundant
	 *
	 * - Strips duplicate node delimiters.
	 * - Replaces instances of "/" with "\\" on Win32 platforms.
	 * - Replaces instances of "\\" with "/" on other platforms.
	 *
	 * @param input
	 *   Path to be normalized.
	 * @return
	 *   Path stripped of duplicate node delimiters & formatted for current system.
	 */
	static std::string norm(const char* input) {
		return norm((std::string) input);
	}

	/** Joins to strings into one using node delimiter.
	 *
	 * @param p1
	 *   First path.
	 * @param p2
	 *   Second path.
	 * @param rem
	 *   Any other paths to be appended.
	 * @return
	 *   Single string in `<p1>/<p2>[/...]` format.
	 */
	template <typename... Args>
	std::string join(std::string p1, std::string p2, Args... rem);

	/**
	 * Converts a path relative to the executable to absolute.
	 *
	 * @param rel
	 *   Relative path.
	 * @return
	 *   Absolute path.
	 */
	std::string rabs(std::string rel);

	/**
	 * Retrieves process executable.
	 *
	 * @return
	 *   Filename path of executed process.
	 */
	std::string getExecutable();

	/**
	 * Retrieves an absolute path to a data resource.
	 *
	 * @param drel
	 *   Path to resource relative to data directory.
	 * @return
	 *   Absolute path to resource.
	 */
	// FIXME: cannot implement this method; linker error
	//~ std::string dataPath(std::string drel);

	/**
	 * Retrieves working directory.
	 *
	 * @return
	 *   Path of current working directory.
	 */
	std::string cwd();

	/**
	 * Changes working directory.
	 *
	 * @param path
	 *   Path of new working directory.
	 * @return
	 *   0 on success.
	 */
	int changeDir(std::string path);

	/** Root directory from where executable is launched. */
	static const std::string dir_root = dirname(getExecutable());
}

#endif /* RRE_PATH */
