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

	bool fexist(const std::string path);

	int mkdir(const std::string path, dperm mode);

	int mkdir(const std::string path);
};

#endif /* RRE_FILESYSTEM */
