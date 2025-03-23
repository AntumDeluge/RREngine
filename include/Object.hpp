/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_OBJECT
#define RRE_OBJECT

#include <cstdint> // *int*_t

#include "Logger.hpp"
#include "SceneImpl.hpp"
#include "ViewportRenderer.hpp"


/**
 * In-game object base class.
 */
class Object {
private:
	static Logger logger;

	/** Objects identifier when added to a scene. */
	uint32_t id;

	// delete `==` operator so `Object.equals` must be used
	bool operator==(const Object&) = delete;

protected:
	Object() {
		// initialize with no scene ID
		id = 0;
	}

public:
	/**
	 * Copy constructor.
	 *
	 * @param other
	 *   Object to be copied.
	 */
	Object(const Object& other) {
		// copied attributes should not include scene ID
		id = 0;
	}

	/** Virtual default destructor. */
	virtual ~Object() = default;

	/** Called every logic step when added to scene. */
	virtual void logic() {
		// does nothing in this implementation
	}

	/**
	 * Checks for equality between this & another object.
	 *
	 * @param other
	 *   Other object to compare against.
	 * @return
	 *   `true` if `other` meets conditions of equality.
	 */
	virtual bool equals(const Object& other) const = 0;

	/**
	 * Checks if this object is instance of a type.
	 */
	template <typename Base>
	bool instanceof() const {
		return dynamic_cast<const Base*>(this) != nullptr;
	}

	/**
	 * Sets object's scene ID.
	 *
	 * @param id
	 *   Identifier to assign to entity in scene.
	 */
	void setId(uint32_t id) { this->id = id; }

	/**
	 * Retrieves object's scene ID.
	 *
	 * @return
	 *   Identifier assigned to object by scene.
	 */
	uint32_t getId() { return id; }

	/**
	 * Callback when added to a scene.
	 *
	 * @param scene
	 *   Scene to which entity has been added.
	 */
	void onAdded(SceneImpl* scene) {
		// inheriting classes can implement
	}

	/**
	 * Draws object sprite on viewport render.
	 *
	 * @param viewport
	 *   Viewport renderer.
	 */
	virtual void render(ViewportRenderer* viewport) = 0;
};

#endif /* RRE_OBJECT */
