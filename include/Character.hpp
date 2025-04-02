/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_CHARACTER
#define RRE_CHARACTER

#include <cstdint> // *int*_t
#include <memory> // std::shared_ptr, std::make_shared
#include <string>

#include "Callable.hpp"
#include "EnergyBar.hpp"
#include "Entity.hpp"
#include "Logger.hpp"
#include "Sprite.hpp"


/**
 * An NPC or playable character.
 */
class Character: public Entity {
private:
	static Logger logger;

	/** Default energy level. */
	uint32_t max_energy = 28;
	uint32_t energy = 28;

	Callable* onDepletedInternal = nullptr;

protected:
	/** Visual representation of entity's current energy level. */
	EnergyBar* energy_bar;

public:
	Character(std::shared_ptr<Sprite> sprite, uint32_t width, uint32_t height);
	Character(std::shared_ptr<Sprite> sprite);

	/** Default constructor. */
	Character();

	/**
	 * Copy constructor.
	 *
	 * @param other
	 *   Character to be copied.
	 */
	Character(const Character& other): Entity(other) {
		if (other.energy_bar) {
			energy_bar = new EnergyBar(*other.energy_bar);
		} else {
			energy_bar = nullptr;
		}
	}

	/** Default destructor. */
	~Character() {
		if (energy_bar) {
			delete energy_bar;
			energy_bar = nullptr;
		}
	}

	/** Overrides `Entity::setBaseEnergy`. */
	void setBaseEnergy(int32_t energy) override;

	void recoverEnergy(uint32_t amount);

	void depleteEnergy(uint32_t amount);

	void onDepleted() {
		if (onDepletedInternal != nullptr) {
			onDepletedInternal->call();
		}
	}

	void setOnDepleted(Callable* onDepleted) {
		onDepletedInternal = onDepleted;
	}

	/** Overrides `Entity::render`. */
	virtual void render(Renderer* ctx) override;
};

#endif /* RRE_CHARACTER */
