/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_DIALOG_H
#define RRE_DIALOG_H

#include <string>


namespace Dialog {
	void info(std::string title, std::string msg);
	void warn(std::string msg);
	void error(std::string msg);
}

#endif /* RRE_DIALOG_H */
