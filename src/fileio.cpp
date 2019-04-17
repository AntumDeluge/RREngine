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

#include "fileio.h"
#include "paths.h"
using namespace std;


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
