/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <algorithm>

#include "Character.hpp"

using namespace std;


Logger Character::logger = Logger::getLogger("Character");

Character::Character(Sprite *sprite, uint32_t width, uint32_t height)
: Entity(sprite, width, height) {
}

Character::Character(Sprite* sprite)
: Entity(sprite) {
}

Character::Character(string sprite_id, uint32_t width, uint32_t height)
: Entity(sprite_id, width, height) {
}

Character::Character(string sprite_id)
: Entity(sprite_id) {
}

void Character::setBaseEnergy(int32_t energy) {
	Entity::setBaseEnergy(energy);
	if (energy_bar) {
		delete energy_bar;
		energy_bar = nullptr;
	}
	energy_bar = new EnergyBar(energy, 24, 25);
}

void Character::recoverEnergy(uint32_t amount) {
	energy = min(energy + amount, max_energy);
}

void Character::depleteEnergy(uint32_t amount) {
	energy = amount > energy ? 0 : energy - amount;
	if (energy == 0) {
		onDepleted();
	}
}

void Character::render(Renderer* ctx) {
	Entity::render(ctx);

	if (energy_bar) {
		energy_bar->render(ctx, energy);
	}
}
