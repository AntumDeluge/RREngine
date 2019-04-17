/* Copyright © 2019 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifdef WIN32
#include <windows.h> // CreateDirectory
#else
#include <sys/stat.h> // mkdir
#endif

#include <iostream>
#include <fstream>

#include "fileio.h"
#include "paths.h"
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
/**
 *
 * @local
 */
int mkdir(const char* path, mode_t mode) {
	cout << "Make dir:" << endl;
	cout << "Path: " << path << endl;
	cout << "Mode: " << mode << endl;

	// FIXME: Second argument is type 'LPSECURITY_ATTRIBUTES' not 'unsigned short/mode_t'
	return CreateDirectory(path, NULL);
}
#endif

int mkdir(const std::string path, mode_t mode) {
	// FIXME: formatPath() should be called in mkdir(char*, mode_t)
	return mkdir(formatPath(path).c_str(), mode);
}

int mkdir(const std::string path) {
	return mkdir(path, NULL);
}
