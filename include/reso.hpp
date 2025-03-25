/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_RESO
#define RRE_RESO

#include <utility> // pair


/**
 * NES native resolution.
 *
 * NOTE: 256x240 appears to be standard NES resolution, but 256x224 might be used as well
 */
const static inline std::pair<int, int> NATIVE_RES = std::pair<int, int>(256, 240);

#endif /* RRE_RESO */
