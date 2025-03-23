/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_GLOBAL_FUNCTIONS
#define RRE_GLOBAL_FUNCTIONS

#include "Player.hpp"


extern Player* GetPlayer();

extern uint8_t GetPlayerDirection();

extern uint8_t AddPlayerDirection(uint8_t dir);

extern uint8_t RemovePlayerDirection(uint8_t dir);

#endif /* RRE_GLOBAL_FUNCTIONS */
