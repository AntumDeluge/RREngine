/* Copyright © 2020 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */


#include <SDL2/SDL_image.h>
#include <tinyxml2.h>

#include "SingletonRepo.h"
#include "Sprite.h"
#include "fileio.h"
#include "paths.h"

using namespace std;
using namespace tinyxml2;


// initialize static logger instance
//~ Logger* Sprite::logger = Logger::getLogger("Sprite");

Sprite::Sprite(string id) {
	this->logger = Logger::getLogger("Sprite");

	this->texture = nullptr;
	this->w = 0;
	this->h = 0;

	// TODO: cache sprites at startup or scene loading (optimization?) in SpriteStore
	const string conf_sprites = concatPath(dir_root, "data/conf/sprites/characters.xml");
	if (!fileExists(conf_sprites)) {
		string msg = "Sprite configuration not found: \"" + conf_sprites + "\"";
		this->logger->error(msg);
		return;
	}

	XMLDocument doc;
	doc.LoadFile(conf_sprites.c_str());
	if (doc.Error()) {
		this->logger->error(doc.ErrorStr());
		return;
	}

	XMLElement* spriteElement = nullptr;
	XMLElement* root = doc.RootElement();
	if (root != nullptr) {
		XMLElement* element = root->FirstChildElement("sprite");
		if (element == nullptr) {
			this->logger->warn("No sprite definitions found in config: \"" + conf_sprites + "\"");
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
		this->logger->error(msg);
		return;
	}

	XMLElement* fileElement = spriteElement->FirstChildElement("filename");
	if (fileElement == nullptr) {
		this->logger->error("Malformed sprite configuration; missing \"filename\" element: \""
				+ conf_sprites + "\"");
	} else {
		string image_path = concatPath(dir_root, (string) "data/sprite/" + fileElement->GetText()
				+ ".png");
		SDL_Surface* surface = IMG_Load(image_path.c_str());
		if (surface == nullptr) {
			this->logger->error("Failed to load image surface: \"" + image_path + "\"");
		} else {
			this->texture = SDL_CreateTextureFromSurface(GetViewport()->getRenderer(), surface);
			SDL_FreeSurface(surface);
		}
	}

	XMLElement* sizeElement = spriteElement->FirstChildElement("size");
	if (sizeElement == nullptr) {
		this->logger->error("Malformed sprite configuration; missing \"size\" element: \""
				+ conf_sprites + "\"");
	} else {
		const XMLAttribute* width = sizeElement->FindAttribute("w");
		const XMLAttribute* height = sizeElement->FindAttribute("h");
		if (width != nullptr) {
			this->w = width->UnsignedValue();
		}
		if (height != nullptr) {
			this->h = height->UnsignedValue();
		}
	}
}

Sprite::Sprite(SDL_Texture* texture, uint32_t w, uint32_t h) {
	this->logger = Logger::getLogger("Sprite");

	this->texture = texture;
	this->w = w;
	this->h = h;
}
