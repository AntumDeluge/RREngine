/* Copyright © 2019-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef FILEIO_H
#define FILEIO_H


#include <string>

extern bool fileExists(const std::string path);

extern int mkdir(const std::string path, mode_t mode);

extern int mkdir(const std::string path);

#endif /* FILEIO_H */
