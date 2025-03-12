/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <utility> // pair


// TODO: rename file to reso.hpp

/**
 * NES native resolution.
 *
 * NOTE: 256x240 appears to be standard NES resolution, but 256x224 might be used as well
 */
const static std::pair<int, int> RES1 = std::pair<int, int>(256, 240);
