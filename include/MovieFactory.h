/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_MOVIE_FACTORY
#define RRE_MOVIE_FACTORY

#include <string>

#include "Movie.h"


namespace MovieFactory {

	Movie* getMovie(std::string id);
}

#endif /* RRE_MOVIE_FACTORY */
