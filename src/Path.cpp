/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <iostream>

#ifdef WIN32
#include <windows.h> // GetModuleFileName, GetCurrentDirectory, SetCurrentDirectory
#else
#include <unistd.h> // readlink, getcwd, chdir
#endif

using namespace std;

#include "Path.h"

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

string Path::basename(string path) {
	path = Path::norm(path);

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

string Path::dirname(string path) {
	path = Path::norm(path);

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
string Path::norm(string input) {

	for (int index = 0; index < input.length(); index++) {
		if (input[index] == replaceNode) {
			input[index] = node;
		}
	}

	return input;
}

string Path::join(const string p1, const string p2) {
	string path = p1 + "/" + p2;

	return Path::norm(path);
}

/** Retrieves the absolute path for the executed file.
 *
 * @function getThisPath
 * @return String path of executable.
 */
string Path::getThisPath() {
	char buffer[PATH_MAX];
#ifdef WIN32
	GetModuleFileName(NULL, buffer, PATH_MAX); // @suppress("Function cannot be resolved")
#else
	readlink("/proc/self/exe", buffer, PATH_MAX); // @suppress("Function cannot be resolved")
#endif
	return (string) buffer;
}

string Path::getCWD() {
	char buffer[PATH_MAX];
#ifdef WIN32
	GetCurrentDirectory(PATH_MAX, buffer); // @suppress("Function cannot be resolved")
#else
	if (getcwd(buffer, PATH_MAX) == NULL) {
		// failed to get CWD so set to relative path
		buffer[0] = '.';
		buffer[1] = '\0';
	}
#endif
	return (string) buffer;
}

int Path::changeDir(string path) {
	int res;
#ifdef WIN32
	res = SetCurrentDirectory(path.c_str()) ? 0 : 1;
#else
	res = chdir(path.c_str());
#endif

	if (res != 0) {
		cerr << "ERROR: failed to change working directory to \"" << path << "\"" << endl;
	}

	return res;
}
