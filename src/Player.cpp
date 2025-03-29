/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "Player.hpp"
#include "reso.hpp"


Logger Player::logger = Logger::getLogger("Player");

Player::Player(Sprite* sprite, uint32_t width, uint32_t height): Character(sprite, width, height) {
	setBaseEnergy(28);
	energy_bar->setOuterColor(228, 229, 148);
	energy_bar->setInnerColor(255, 254, 255);
}

Player::Player(Sprite* sprite): Character(sprite) {
	setBaseEnergy(28);
	energy_bar->setOuterColor(228, 229, 148);
	energy_bar->setInnerColor(255, 254, 255);
}

Player::Player(std::string sprite_id, uint32_t width, uint32_t height)
: Character(sprite_id, width, height) {
	setBaseEnergy(28);
	energy_bar->setOuterColor(228, 229, 148);
	energy_bar->setInnerColor(255, 254, 255);
}

Player::Player(std::string sprite_id): Character(sprite_id) {
	setBaseEnergy(28);
	energy_bar->setOuterColor(228, 229, 148);
	energy_bar->setInnerColor(255, 254, 255);
}

Player::Player(const Player& other): Character(other) {
	if (!energy_bar) {
		setBaseEnergy(28);
		energy_bar->setOuterColor(228, 229, 148);
		energy_bar->setInnerColor(255, 254, 255);
	}
}


void Player::logic() {
	Entity::logic();

	if (rect.x != x_prev || rect.y != y_prev) {
		onMoved();
	}
	x_prev = rect.x;
	y_prev = rect.y;
}

void Player::onAdded(SceneImpl* scene) {
	Object::onAdded(scene);

	x_prev = rect.x;
	y_prev = rect.y;
}

void Player::onMoved() {
	uint32_t half_res_w = NATIVE_RES.first / 2;
	int32_t p_center = rect.x + (rect.w / 2);
	int32_t diff = p_center - half_res_w;
	if (diff > 0 && p_center < scene->getWidth() - half_res_w) {
		scene->setOffsetX(diff);
	}
}
