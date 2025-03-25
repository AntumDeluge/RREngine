/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "GameVisuals.hpp"


Logger GameVisuals::logger = Logger::getLogger("GameVisuals");

// initialize singleton instance
unique_ptr<GameVisuals> GameVisuals::instance = nullptr;
mutex GameVisuals::mtx;
