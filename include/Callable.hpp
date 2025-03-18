/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_CALLABLE
#define RRE_CALLABLE

#include <functional>


class Callable {
private:
	const std::function<void()> func;

public:
	Callable(std::function<void()> func): func(func) {}

	void call() {
		func();
	}
};

#endif /* RRE_CALLABLE */
