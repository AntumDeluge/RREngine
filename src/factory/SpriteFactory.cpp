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
#include "StrUtil.hpp"
#include "TextureLoader.hpp"
#include "factory/SpriteFactory.hpp"

using namespace std;
using namespace pugi;


static Logger _logger = Logger::getLogger("SpriteFactory");

shared_ptr<Sprite> SpriteFactory::build(xml_node el) {
	xml_node el_filename = el.child("filename");
	if (el_filename.type() == node_null) {
		_logger.error("Filename not configured");
		return nullptr;
	}

	uint32_t width = 0, height = 0;
	xml_node el_size = el.child("size");
	if (el_size.type() != node_null) {
		xml_attribute attr_width = el_size.attribute("width");
		if (!attr_width.empty()) {
			width = StrUtil::toUInt(attr_width.value());
		}
		xml_attribute attr_height = el_size.attribute("height");
		if (!attr_height.empty()) {
			height = StrUtil::toUInt(attr_height.value());
		}
	}

	if (width == 0 or height == 0) {
		_logger.warn("Sprite with invalid dimensions: " + to_string(width) + "x"
				+ to_string(height));
	}

	string default_mode = "";
	unordered_map<string, Animation> animation_modes;
	xml_node el_animation = el.child("animation");
	while (el_animation.type() != node_null) {
		string mode_name = "";
		AnimationFrameSet current_frames;

		xml_attribute attr_mode = el_animation.attribute("mode");
		if (!attr_mode.empty()) {
			mode_name = attr_mode.value();
		}
		if (mode_name.compare("") == 0) {
			_logger.error("XML Parsing Error: Animation frame without \"mode\" attribute");
			return nullptr;
		}

		xml_attribute attr_default = el_animation.attribute("default");
		if (mode_name.compare("") == 0 || (!attr_default.empty()
				&& StrUtil::toBool(attr_default.value()))) {
			default_mode = mode_name;
		}

		xml_node el_frame = el_animation.child("frame");
		while (el_frame.type() != node_null) {
			xml_attribute attr_index = el_frame.attribute("index");
			xml_attribute attr_delay = el_frame.attribute("delay");
			if (!attr_index.empty() && !attr_delay.empty()) {
				current_frames.push_back(AnimationFrame(StrUtil::toUInt(attr_index.value()),
						StrUtil::toUInt(attr_delay.value())));
			}

			el_frame = el_frame.next_sibling("frame");
		}

		if (current_frames.size() == 0) {
			_logger.error("XML Parsing Error: Animation without frames");
			return nullptr;
		}
		Animation ani = Animation(true, current_frames);
		ani.setId(mode_name);
		animation_modes[mode_name] = ani;

		el_animation = el_animation.next_sibling("animation");
	}

	shared_ptr<Sprite> sprite_ptr;
	SDL_Texture* texture = TextureLoader::load(Path::join("sprite", el_filename.text().get()));
	if (animation_modes.size() > 0) {
		// animated sprite
		sprite_ptr = make_shared<AnimatedSprite>(texture, width, height);
		((AnimatedSprite*) sprite_ptr.get())->setModes(animation_modes);
		((AnimatedSprite*) sprite_ptr.get())->setDefaultMode(default_mode);
		((AnimatedSprite*) sprite_ptr.get())->setMode(default_mode);
	} else {
		// static sprite
		uint32_t tile_index = 0;
		xml_attribute attr_index = el_filename.attribute("index");
		if (!attr_index.empty()) {
			tile_index = StrUtil::toUInt(attr_index.value());
		}
		sprite_ptr = make_shared<Sprite>(texture, width, height, tile_index);
	}

	if (!sprite_ptr->ready()) {
		xml_attribute attr_id = el.attribute("id");
		if (!attr_id.empty()) {
			_logger.warn("Built uninitialized sprite: " + string(attr_id.value()));
		} else {
			_logger.warn("Built uninitialized sprite");
		}
	}

	return sprite_ptr;
}
