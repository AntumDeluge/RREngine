/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_MOVIE_FACTORY
#define RRE_MOVIE_FACTORY

#include <string>

#include "Movie.h"


/**
 * Manages configured movies.
 *
 * TODO:
 * - rename file to MovieFactory.hpp
 * - move to factory directory
 */
namespace MovieFactory {

	/**
	 * Builds & retrieves a configured movie.
	 *
	 * @param id
	 *   Movie identifier.
	 * @return
	 *   Move instance or `null` if not configured.
	 */
	Movie* getMovie(std::string id);
}

#endif /* RRE_MOVIE_FACTORY */
