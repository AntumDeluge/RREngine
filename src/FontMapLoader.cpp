/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <string>
#include <vector>

#include "Filesystem.h"
#include "FontMap.h"
#include "FontMapLoader.h"
#include "FontStore.h"
#include "dialog.h"
#include "paths.h"

using namespace std;
using namespace tinyxml2;


// initialize static members
FontMapLoader* FontMapLoader::instance = nullptr;

void FontMapLoader::loadConfig() {
	if (this->loaded) {
		logger->warn("Cannot reload font maps");
		return;
	}
	this->loaded = true;

	string conf_fonts = concatPath(dir_root, "data/conf/fonts.xml");
	this->logger->debug("Loading fonts config: \"" + conf_fonts + "\"");
	if (!fileExists(conf_fonts)) {
		this->logger->warn("Fonts config not found: \"" + conf_fonts + "\"");
		return;
	}

	XMLDocument doc;
	if (doc.LoadFile(conf_fonts.c_str()) != 0) {
		string msg = "Failed to load fonts config: \"" + conf_fonts + "\"";
		this->logger->error(msg);
		Dialog::error(msg);
		return;
	}

	XMLElement* root = doc.RootElement();
	if (root == nullptr) {
		string msg = "Malformed config missing root element: \"" + conf_fonts + "\"";
		this->logger->error(msg);
		Dialog::error(msg);
		return;
	}

	XMLElement* el = root->FirstChildElement("font");
	while (el != nullptr) {
		if (!this->parseFont(el)) {
			break;
		}
		el = el->NextSiblingElement("font");
	}
}

bool FontMapLoader::parseFont(XMLElement* el) {
	vector<string> err;

	string id = "";
	string path = "";
	int w = 0;
	int h = 0;

	XMLAttribute* attr = (XMLAttribute*) el->FindAttribute("id");
	if (attr == nullptr) {
		err.push_back("Missing font attribute \"id\"");
	} else {
		id = attr->Value();
	}

	attr = (XMLAttribute*) el->FindAttribute("tileset");
	if (attr == nullptr) {
		err.push_back("Missing font attribute \"tileset\"");
	} else {
		path = concatPath(dir_root, (string) "data/tileset/" + attr->Value());
		if (!fileExists(path)) {
			err.push_back("Missing font bitmap file: \"" + path + "\"");
		}
	}

	attr = (XMLAttribute*) el->FindAttribute("w");
	if (attr == nullptr) {
		err.push_back("Missing font attribute \"w\"");
	} else {
		w = attr->IntValue();
	}

	attr = (XMLAttribute*) el->FindAttribute("h");
	if (attr == nullptr) {
		err.push_back("Missing font attribute \"h\"");
	} else {
		h = attr->IntValue();
	}

	if (!err.empty()) {
		string msg = "";
		for (int idx = 0; idx < err.size(); idx++) {
			if (msg.length() > 0) {
#ifdef WIN32
				msg += "\r\n";
#else
				msg += "\n";
#endif
			}
			msg += err[idx];
		}
		this->logger->error("XML Parsing Errors: " + msg);
		Dialog::error("XML Parsing Errors", msg);
		return false;
	}

	unordered_map<wchar_t, int> char_map = this->parseCharacters(el);
	if (char_map.size() == 0) {
		return false;
	}

	FontStore::addMap(id, new FontMap(path, char_map, w, h));

	return true;
}

unordered_map<wchar_t, int> FontMapLoader::parseCharacters(XMLElement* el) {
	unordered_map<wchar_t, int> empty_map;
	unordered_map<wchar_t, int> char_map;

	XMLElement* cel = el->FirstChildElement("char");
	while (cel != nullptr) {
		const XMLAttribute* attr = cel->FindAttribute("index");
		if (attr == nullptr) {
			string msg = "Missing attribute \"index\" in XML element \"char\"";
			this->logger->error("XML Parsing Error: " + msg);
			Dialog::error("XML Parsing Error", msg);
			return empty_map;
		}

		const int start_index = attr->IntValue();
		const string value = cel->GetText();
		for (int idx = 0; idx < value.length(); idx++) {
			int index_offset = start_index + idx;
			wchar_t c = value[idx];
			char_map[c] = index_offset;
		}

		cel = cel->NextSiblingElement("char");
	}

	if (char_map.size() == 0) {
		string msg = "No character mappings defined";
		this->logger->error("XML Parsing Error: " + msg);
		Dialog::error("XML Parsing Error", msg);
	}

	return char_map;
}
