/* Copyright © 2019-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FILESYSTEM
#define RRE_FILESYSTEM

#include <string>

#ifdef WIN32
typedef unsigned char dperm; // placeholder
#else
#include <sys/stat.h> // mode_t, mkdir
typedef mode_t dperm;
#endif


namespace Filesystem {

	bool fileExists(const std::string path);

	#ifdef WIN32
	/**
	 * `mkdir` function not defined on Windows.
	 *
	 * @param path Path of directory that should be created.
	 * @param mode Permissions of new directory (Calls should compensate for both Windows & Unix type
	 *     permissions.
	 */
	int mkdir(const char* path, dperm mode);
	#endif

	int mkdir(const char* path);

	int mkdir(const std::string path, dperm mode);

	int mkdir(const std::string path);
};

#endif /* RRE_FILESYSTEM */
