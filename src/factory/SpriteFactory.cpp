/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <cstdint> // *int*_t
#include <string>

#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "factory/SpriteFactory.hpp"

using namespace std;
using namespace tinyxml2;


static Logger _logger = Logger::getLogger("SpriteFactory");

Sprite SpriteFactory::build(XMLElement* el) {
	Sprite sprite;

	XMLElement* el_filename = el->FirstChildElement("filename");
	if (el_filename == nullptr) {
		_logger.error("Filename not configured");
		// uninitialized object
		return sprite;
	}

	uint32_t width = 0, height = 0;
	XMLElement* el_size = el->FirstChildElement("size");
	if (el_size != nullptr) {
		const XMLAttribute* attr_width = el_size->FindAttribute("width");
		if (attr_width != nullptr) {
			width = attr_width->UnsignedValue();
		}
		const XMLAttribute* attr_height = el_size->FindAttribute("height");
		if (attr_height != nullptr) {
			height = attr_height->UnsignedValue();
		}
	}

	if (width == 0 or height == 0) {
		_logger.warn("Sprite with invalid dimensions: " + to_string(width) + "x"
				+ to_string(height));
	}

	AnimationFrameSet frames;
	XMLElement* el_animation = el->FirstChildElement("animation");
	if (el_animation != nullptr) {
		XMLElement* el_f = el_animation->FirstChildElement("frame");
		while (el_f != nullptr) {
			const XMLAttribute* attr_index = el_f->FindAttribute("index");
			const XMLAttribute* attr_delay = el_f->FindAttribute("delay");
			if (attr_index != nullptr && attr_delay != nullptr) {
				frames.push_back(AnimationFrame(attr_index->UnsignedValue(),
						attr_delay->UnsignedValue()));
			}

			el_f = el_f->NextSiblingElement("frame");
		}
	}

	string filename = el_filename->GetText();
	if (frames.size() > 0) {
		// animated sprite
		sprite = AnimatedSprite(filename, width, height);
	} else {
		// static sprite
		sprite = Sprite(filename, width, height);
	}

	return sprite;
}
