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

extern std::string getThisPath();

