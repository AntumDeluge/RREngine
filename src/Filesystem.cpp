/* Copyright © 2019-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <fstream>

#ifdef WIN32
#include <windows.h> // CreateDirectory
#endif

#include "Filesystem.h"

using namespace std;


/** Checks for existing file.
 *
 * @function fileExists
 * @param path String path to file.
 * @return `true` if the file is found in the filesystem.
 */
bool fileExists(const string path) {
	ifstream ofile;
	ofile.open(path);
	bool exists = ofile.is_open();
	ofile.close();

	return exists;
}

#ifdef WIN32
int mkdir(const char* path, dperm mode) {
	// FIXME: `mode` must be LPSECURITY_ATTRIBUTES
	return CreateDirectory(path, NULL);
}
#endif

int mkdir(const char* path) {
	return mkdir(path, '\0');
}

int mkdir(const std::string path, dperm mode) {
	return mkdir(path.c_str(), mode);
}

int mkdir(const std::string path) {
	return mkdir(path, '\0');
}
