/* Copyright © 2018 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifdef WIN32
#include <windows.h> // GetModuleFileName
#else
#include <unistd.h> // readlink
#endif

#include "paths.h"
using namespace std;

#ifdef WIN32
const char replaceNode = '/';
const char node = '\\';
#else
const char replaceNode = '\\';
const char node = '/';
#endif


/** Checks if a string contains a specified character.
 *
 * @function contains
 * @param input String to be parsed.
 * @param value Character to be searched for.
 * @return `true` if the character is found in string.
 */
bool contains(const string input, const char value) {
	for (int idx = 0; idx < input.length(); idx++) {
		if (input[idx] == value) {
			return true;
		}
	}

	return false;
}

string basename(string path) {
	path = formatPath(path);

	if (!contains(path, node)) {
		return path;
	}

	int cutoff;
	for (int idx = path.length() - 1; idx >= 0; idx--) {
		if (path[idx] == node) {
			cutoff = idx;
			break;
		}
	}

	return path.substr(cutoff + 1, path.length() - (cutoff + 1));
}

string dirname(string path) {
	path = formatPath(path);

	if (!contains(path, node)) {
		return path;
	}

	int cutoff;
	for (int idx = path.length() - 1; idx >= 0; idx--) {
		if (path[idx] == node) {
			cutoff = idx;
			break;
		}
	}

	return path.substr(0, cutoff);
}

/** Converts node delimiters in a string to conform with current system.
 *
 * @function formatPath
 * @param input String to be formatted.
 * @return Formatted string.
 */
string formatPath(string input) {

	for (int index = 0; index < input.length(); index++) {
		if (input[index] == replaceNode) {
			input[index] = node;
		}
	}

	return input;
}

/** Retrieves the absolute path for the executed file.
 *
 * @function getThisPath
 * @return String path of executable.
 */
string getThisPath() {
	char* buffer;
#ifdef WIN32
	GetModuleFileName(NULL, buffer, PATH_MAX); // @suppress("Function cannot be resolved")
#else
	readlink("/proc/self/exe", buffer, PATH_MAX); // @suppress("Function cannot be resolved")
#endif
	return (string) buffer;
}
