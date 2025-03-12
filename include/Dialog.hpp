/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_DIALOG
#define RRE_DIALOG

#include <string>


/**
 * Wrapper for displaying notification dialogs.
 */
namespace Dialog {

	/**
	 * Displays a message dialog with "info" level urgency.
	 *
	 * @param title
	 *   Window title text.
	 * @param msg
	 *   Window contents text.
	 */
	void info(std::string title, std::string msg);

	/**
	 * Displays a message dialog with "warning" level urgency.
	 *
	 * @param title
	 *   Window title text.
	 * @param msg
	 *   Window contents text.
	 */
	void warn(std::string title, std::string msg);

	/**
	 * Displays a message dialog with "warning" level urgency.
	 *
	 * @param msg
	 *   Window contents text.
	 */
	void warn(std::string msg);

	/**
	 * Displays a message dialog with "error" level urgency.
	 *
	 * @param title
	 *   Window title text.
	 * @param msg
	 *   Window contents text.
	 */
	void error(std::string title, std::string msg);

	/**
	 * Displays a message dialog with "error" level urgency.
	 *
	 * @param msg
	 *   Window contents text.
	 */
	void error(std::string msg);
}

#endif /* RRE_DIALOG */
