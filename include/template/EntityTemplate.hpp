/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_ENTITY_TEMPLATE
#define RRE_ENTITY_TEMPLATE

#include <memory> // std::shared_ptr, std::make_shared

#include "Character.hpp"
#include "Entity.hpp"
#include "HashObject.hpp"
#include "Logger.hpp"
#include "Player.hpp"
#include "Sprite.hpp"


class EntityTemplate: public HashObject {
private:
	static Logger logger;

	std::shared_ptr<Sprite> sprite;

	void updateAttributes(std::shared_ptr<Entity> entity);

public:
	/** Default constructor. */
	EntityTemplate();

	void setSprite(std::shared_ptr<Sprite> sprite) { this->sprite = sprite; }

	std::shared_ptr<Entity> build();

	std::shared_ptr<Character> buildCharacter();

	std::shared_ptr<Player> buildPlayer();
};

#endif /* RRE_ENTITY_TEMPLATE */
