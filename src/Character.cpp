/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "Character.hpp"

using namespace std;


Logger Character::logger = Logger::getLogger("Character");

Character::Character(shared_ptr<Sprite> sprite, uint32_t width, uint32_t height)
: Entity(sprite, width, height) {
	energy_bar = nullptr;
}

Character::Character(shared_ptr<Sprite> sprite)
: Entity(sprite) {
	energy_bar = nullptr;
}

Character::Character() {
	energy_bar = nullptr;
}

void Character::setBaseEnergy(int32_t energy) {
	Entity::setBaseEnergy(energy);
	if (energy_bar) {
		delete energy_bar;
		energy_bar = nullptr;
	}
	energy_bar = new EnergyBar(energy, 24, 25);
}

void Character::render(Renderer* ctx) {
	Entity::render(ctx);

	if (energy_bar) {
		energy_bar->render(ctx, energy);
	}
}
