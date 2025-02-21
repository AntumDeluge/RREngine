/* Copyright © 2019-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FILEIO_H
#define RRE_FILEIO_H

#include <string>

#ifdef WIN32
typedef unsigned char dperm; // placeholder
#else
#include <sys/stat.h> // mode_t, mkdir
typedef mode_t dperm;
#endif


extern bool fileExists(const std::string path);

#ifdef WIN32
/**
 * `mkdir` function not defined on Windows.
 *
 * @param path Path of directory that should be created.
 * @param mode Permissions of new directory (Calls should compensate for both Windows & Unix type
 *     permissions.
 */
extern int mkdir(const char* path, dperm mode);
#endif

extern int mkdir(const char* path);

extern int mkdir(const std::string path, dperm mode);

extern int mkdir(const std::string path);

#endif /* RRE_FILEIO_H */
