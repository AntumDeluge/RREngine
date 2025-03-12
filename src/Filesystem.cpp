/* Copyright © 2019-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <fstream>
#ifdef __WIN32__
#include <windows.h> // CreateDirectory
#endif

#include "Filesystem.hpp"

using namespace std;


bool Filesystem::fexist(const string path) {
	ifstream ofile;
	ofile.open(path);
	bool exists = ofile.is_open();
	ofile.close();

	return exists;
}

int Filesystem::mkdir(const string path, dperm mode) {
#ifdef __WIN32__
	// FIXME: `mode` must be LPSECURITY_ATTRIBUTES
	return CreateDirectory(path.c_str(), NULL);
#else
	return mkdir(path.c_str(), mode);
#endif
}

int Filesystem::mkdir(const string path) {
	return Filesystem::mkdir(path, '\0');
}

vector<filesystem::directory_entry> Filesystem::listDir(string path, bool recurse) {
	vector<filesystem::directory_entry> items;
	if (recurse) {
		for (filesystem::directory_entry item: filesystem::recursive_directory_iterator{path}) {
			items.push_back(item);
		}
	} else {
		for (filesystem::directory_entry item: filesystem::directory_iterator{path}) {
			items.push_back(item);
		}
	}
	return items;
}
