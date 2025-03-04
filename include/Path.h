/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_PATH
#define RRE_PATH

#include <string>


namespace Path {

	std::string basename(std::string path);

	std::string dirname(std::string path);

	std::string norm(std::string input);

	static std::string norm(const char* input) {
		return norm((std::string) input);
	}

	/** Joins to strings into one using node delimiter.
	 *
	 * @param p1 First path.
	 * @param p2 Second path.
	 * @return Single string in `p1/p2` format.
	 */
	std::string join(const std::string p1, const std::string p2);

	/**
	 * Converts a path relative to the executable to absolute.
	 *
	 * @param rel
	 *   Relative path.
	 * @return
	 *   Absolute path.
	 */
	std::string rabs(std::string rel);

	std::string getExecutable();

	std::string cwd();

	int changeDir(std::string path);

	/** Root directory from where executable is launched. */
	static const std::string dir_root = dirname(getExecutable());
}

	#endif /* RRE_PATH */
