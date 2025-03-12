/* Copyright © 2019-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FILESYSTEM
#define RRE_FILESYSTEM

#include <filesystem>
#include <string>
#include <vector>

#ifdef __WIN32__
typedef unsigned char dperm; // placeholder
#else
#include <sys/stat.h> // mode_t, mkdir
typedef mode_t dperm;
#endif


/**
 * Wrapper for filesystem related functions.
 */
namespace Filesystem {

	/** Checks for existing file.
	 *
	 * @param path
	 *   String path to file.
	 * @return
	 *   `true` if the file is found in the filesystem.
	 * @deprecated
	 *   Replace with calls to `std::filesystem::is_regular_file`
	 */
	bool fexist(const std::string path);

	/**
	 * Creates a new directory tree in the filesystem.
	 *
	 * FIXME: unused?
	 *
	 * @param path
	 *   Path to new directory.
	 * @param mode
	 *   Directory permissions.
	 */
	int mkdir(const std::string path, dperm mode);

	/**
	 * Creates a new directory tree in the filesystem with default permissions.
	 *
	 * FIXME: unused?
	 *
	 * @param path
	 *   Path to new directory.
	 */
	int mkdir(const std::string path);

	/**
	 * Retrieves contents of a system directory.
	 *
	 * @param path
	 *   Path to directory to be examined.
	 * @param recurse
	 *   If `true`, get contents of sub-directories recursively.
	 * @return
	 *   List of directory objects.
	 */
	std::vector<std::filesystem::directory_entry> listDir(std::string path, bool recurse);

	/**
	 * Retrieves contents of a system directory without recursion.
	 *
	 * @param path
	 *   Path to directory to be examined.
	 * @return
	 *   List of directory objects.
	 */
	static inline std::vector<std::filesystem::directory_entry> listDir(std::string path) {
		return listDir(path, false);
	}
};

#endif /* RRE_FILESYSTEM */
