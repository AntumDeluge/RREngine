/* Copyright © 2020 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

//~ #include <SDL2/SDL_image.h>
#include <tinyxml2.h>

using namespace tinyxml2;

#include "Filesystem.h"
#include "Logger.h"
#include "Path.h"
#include "Sprite.h"
#include "TextureLoader.h"

using namespace std;


Logger Sprite::logger = Logger::getLogger("Sprite");

Sprite::Sprite(string id) : ImageImpl() {
	// TODO: cache sprites at startup or scene loading (optimization?) in SpriteStore
	const string conf_sprites = Path::join(Path::dir_root, "data/conf/sprites/characters.xml");
	if (!Filesystem::fexist(conf_sprites)) {
		string msg = "Sprite configuration not found: \"" + conf_sprites + "\"";
		this->logger.error(msg);
		return;
	}

	XMLDocument doc;
	doc.LoadFile(conf_sprites.c_str());
	if (doc.Error()) {
		this->logger.error(doc.ErrorStr());
		return;
	}

	XMLElement* spriteElement = nullptr;
	XMLElement* root = doc.RootElement();
	if (root != nullptr) {
		XMLElement* element = root->FirstChildElement("sprite");
		if (element == nullptr) {
			this->logger.warn("No sprite definitions found in config: \"" + conf_sprites + "\"");
		}

		while (element != nullptr) {
			const XMLAttribute* attr = element->FindAttribute("id");
			if (id.compare(attr->Value()) == 0) {
				spriteElement = element;
				break;
			}

			element = element->NextSiblingElement("sprite");
		}
	}

	if (spriteElement == nullptr) {
		string msg = "Sprite for ID \"" + id + "\" not configured: \"" + conf_sprites + "\"";
		this->logger.error(msg);
		return;
	}

	XMLElement* fileElement = spriteElement->FirstChildElement("filename");
	if (fileElement == nullptr) {
		this->logger.error("Malformed sprite configuration; missing \"filename\" element: \""
				+ conf_sprites + "\"");
	} else {
		this->texture = TextureLoader::load(Path::join("sprite", fileElement->GetText()));
	}

	XMLElement* sizeElement = spriteElement->FirstChildElement("size");
	if (sizeElement == nullptr) {
		this->logger.error("Malformed sprite configuration; missing \"size\" element: \""
				+ conf_sprites + "\"");
	} else {
		const XMLAttribute* width = sizeElement->FindAttribute("w");
		const XMLAttribute* height = sizeElement->FindAttribute("h");
		if (width != nullptr) {
			this->width = width->UnsignedValue();
		}
		if (height != nullptr) {
			this->height = height->UnsignedValue();
		}
	}
}
