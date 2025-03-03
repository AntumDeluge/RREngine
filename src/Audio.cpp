/* Copyright © 2020-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <tinyxml2.h>

#include "Dialog.h"
#include "Audio.h"
#include "Filesystem.h"
#include "Path.h"

using namespace tinyxml2;


// TODO: cache audio files
std::string Audio::GetMusicFile(const std::string id) {
	std::string conf_music = concatPath(dir_root, "data/conf/music.xml");
	if (!Filesystem::fexist(conf_music)) {
		Dialog::error("Music config not found: \"" + conf_music + "\"");
		return "";
	}

	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(conf_music.c_str()) != 0) {
		Dialog::error("Failed to load music config: \"" + conf_music + "\"");
		return "";
	}

	std::string file_music = "";

	XMLElement* root = doc.RootElement(); // TODO: check that root element exists
	if (root == NULL || root == nullptr) {
		Dialog::error("Missing root \"music\" element in music config: \"" + conf_music + "\"");
		return "";
	}

	XMLElement* el = root->FirstChildElement("file");
	while (el != NULL) {
		const XMLAttribute* attr = el->FindAttribute("id");
		if (attr != NULL && id.compare(attr->Value()) == 0) {
			// found element with matching ID
			file_music = concatPath(dir_root, ((std::string) "data/music/") + el->GetText());
			if (Filesystem::fexist(file_music + ".oga")) {
				file_music += ".oga";
			} else if (Filesystem::fexist(file_music + ".ogg")) {
				file_music += ".ogg";
			} else {
				file_music = "";
			}
			break;
		}

		el = root->NextSiblingElement("file");
	}

	return file_music;
}
