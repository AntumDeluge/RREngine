/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <cstdint> // *int*_t
#include <string>
#include <unordered_map>

#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "Path.hpp"
#include "TextureLoader.hpp"
#include "factory/SpriteFactory.hpp"

using namespace std;
using namespace tinyxml2;


static Logger _logger = Logger::getLogger("SpriteFactory");

shared_ptr<Sprite> SpriteFactory::build(XMLElement* el) {
	XMLElement* el_filename = el->FirstChildElement("filename");
	if (el_filename == nullptr) {
		_logger.error("Filename not configured");
		return nullptr;
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

	string default_mode = "";
	unordered_map<string, Animation> animation_modes;
	XMLElement* el_animation = el->FirstChildElement("animation");
	while (el_animation) {
		string mode_name = "";
		AnimationFrameSet current_frames;

		const XMLAttribute* attr_mode = el_animation->FindAttribute("mode");
		if (attr_mode) {
			mode_name = attr_mode->Value();
		}
		if (mode_name.compare("") == 0) {
			_logger.error("XML Parsing Error: Animation frame without \"mode\" attribute");
			return nullptr;
		}

		const XMLAttribute* attr_default = el_animation->FindAttribute("default");
		if (mode_name.compare("") == 0 || (attr_default && attr_default->BoolValue())) {
			default_mode = mode_name;
		}

		XMLElement* el_frame = el_animation->FirstChildElement("frame");
		while (el_frame) {
			const XMLAttribute* attr_index = el_frame->FindAttribute("index");
			const XMLAttribute* attr_delay = el_frame->FindAttribute("delay");
			if (attr_index != nullptr && attr_delay != nullptr) {
				current_frames.push_back(AnimationFrame(attr_index->UnsignedValue(),
						attr_delay->UnsignedValue()));
			}

			el_frame = el_frame->NextSiblingElement("frame");
		}

		if (current_frames.size() == 0) {
			_logger.error("XML Parsing Error: Animation without frames");
			return nullptr;
		}
		Animation ani = Animation(true, current_frames);
		ani.setId(mode_name);
		animation_modes[mode_name] = ani;

		el_animation = el_animation->NextSiblingElement("animation");
	}

	shared_ptr<Sprite> sprite_ptr;
	SDL_Texture* texture = TextureLoader::load(Path::join("sprite", el_filename->GetText()));
	if (animation_modes.size() > 0) {
		// animated sprite
		sprite_ptr = make_shared<AnimatedSprite>(texture, width, height);
		((AnimatedSprite*) sprite_ptr.get())->setModes(animation_modes);
		((AnimatedSprite*) sprite_ptr.get())->setDefaultMode(default_mode);
		((AnimatedSprite*) sprite_ptr.get())->setMode(default_mode);
	} else {
		// static sprite
		uint32_t tile_index = 0;
		const XMLAttribute* attr_index = el_filename->FindAttribute("index");
		if (attr_index) {
			tile_index = attr_index->UnsignedValue();
		}
		sprite_ptr = make_shared<Sprite>(texture, width, height, tile_index);
	}

	if (!sprite_ptr->ready()) {
		const XMLAttribute* attr_id = el->FindAttribute("id");
		if (attr_id) {
			_logger.warn("Built uninitialized sprite: " + string(attr_id->Value()));
		} else {
			_logger.warn("Built uninitialized sprite");
		}
	}

	return sprite_ptr;
}
