/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_MOMENTUM_DIR
#define RRE_MOMENTUM_DIR

#include <cstdint> // *int*_t


namespace MomentumDir {
	/** Enumeration representing entity direction of momentum. */
	enum Dir: uint8_t {
		NONE =  0,
		LEFT =  1 << 0,
		RIGHT = 1 << 1,
		UP =    1 << 2,
		DOWN =  1 << 3
	};
}

#endif /* RRE_MOMENTUM_DIR */
