/* Copyright © 2018 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <string>


extern std::string basename(std::string path);

extern std::string dirname(std::string path);

extern std::string formatPath(std::string input);

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
extern std::string concatPath(const std::string p1, const std::string p2);

extern std::string getThisPath();
