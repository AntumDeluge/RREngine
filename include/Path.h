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

	std::string formatPath(std::string input);

	static std::string formatPath(const char* input) {
		return formatPath((std::string) input);
	}

	/** Joins to strings into one using node delimiter.
	 *
	 * @function concatPath
	 * @param p1 First path.
	 * @param p2 Second path.
	 * @return Single string in `p1/p2` format.
	 */
	std::string concatPath(const std::string p1, const std::string p2);

	std::string getThisPath();

	std::string getCWD();

	int changeDir(std::string path);

	/** Root directory from where executable is launched. */
	static const std::string dir_root = dirname(getThisPath());
}

	#endif /* RRE_PATH */
