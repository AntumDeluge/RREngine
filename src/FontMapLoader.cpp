/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <cstddef> // size_t
#include <cstdint> // uint*_t
#include <string>
#include <unordered_map>
#include <vector>

#include <tinyxml2.h>

#include "Dialog.hpp"
#include "Filesystem.hpp"
#include "FontMap.hpp"
#include "FontMapLoader.hpp"
#include "FontStore.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "TextureLoader.hpp"
#include "builtin/conf/fonts.h"
#if HAVE_BUILTIN_FONT_MAP
#include "builtin/tileset/fontmap_png.h"
#endif

using namespace std;
using namespace tinyxml2;


namespace FontMapLoader {
	/** Logger instance dedicated to namespace. */
	Logger logger = Logger::getLogger("FontMapLoader");

	bool loaded = false;
};

/**
 * Parses mapping of character index.
 *
 * @param el
 *   Element containing starting index & associated characters.
 * @return
 *   Mapping of indexed characters.
 */
unordered_map<wchar_t, int> _parseCharacters(XMLElement* el) {
	unordered_map<wchar_t, int> empty_map;
	unordered_map<wchar_t, int> char_map;

	XMLElement* cel = el->FirstChildElement("char");
	while (cel != nullptr) {
		const XMLAttribute* attr = cel->FindAttribute("index");
		if (attr == nullptr) {
			string msg = "Missing attribute \"index\" in XML element \"char\"";
			FontMapLoader::logger.error("XML Parsing Error: " + msg);
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
		FontMapLoader::logger.error("XML Parsing Error: " + msg);
		Dialog::error("XML Parsing Error", msg);
	}

	return char_map;
}

/**
 * Creates a font map from XML data.
 *
 * @param el
 *   Element containing font information.
 * @param data
 *   PNG image data to use for map texture. if `NULL`, uses path parsed from XML.
 * @param data_size
 *   Data's byte count to be read.
 * @return
 *   `true` if parsing succeeded.
 */
bool _parseFont(XMLElement* el, const uint8_t data[], const size_t data_size) {
	vector<string> err;

	string id = "";
	string rpath = "";
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
		rpath = Path::join("tileset", attr->Value());
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
#ifdef __WIN32__
				msg += "\r\n";
#else
				msg += "\n";
#endif
			}
			msg += err[idx];
		}
		FontMapLoader::logger.error("XML Parsing Errors: " + msg);
		Dialog::error("XML Parsing Errors", msg);
		return false;
	}

	unordered_map<wchar_t, int> char_map = _parseCharacters(el);
	if (char_map.size() == 0) {
		return false;
	}

	// add parsed data to font store
	if (data != nullptr) {
		FontStore::addMap(id, new FontMap(TextureLoader::loadFM(data, data_size), char_map, w, h));
	} else {
		FontStore::addMap(id, new FontMap(TextureLoader::load(rpath), char_map, w, h));
	}

	return true;
}


bool FontMapLoader::loadBuiltin() {
#if RRE_DEBUGGING
	FontMapLoader::logger.debug("Loading built-in fonts config");
#endif

	XMLDocument doc;
	if (doc.Parse(builtin_fonts_config.c_str()) != XML_SUCCESS) {
		string msg = "Failed to load built-in fonts config";
		FontMapLoader::logger.error(msg);
		Dialog::error(msg);
		return false;
	}

	XMLElement* root = doc.FirstChildElement("fonts");
	if (root == nullptr) {
		string msg = "Root element \"fonts\" not found";
		FontMapLoader::logger.error("XML Parsing Error: " + msg);
		Dialog::error("XML Parsing Error", msg);
		return false;
	}

	XMLElement* el = root->FirstChildElement("font");
	if (el == nullptr) {
		string msg = "Built-in font not configured";
		FontMapLoader::logger.error("XML Parsing Error: " + msg);
		Dialog::error("XML Parsing Error", msg);
		return false;
	}

#if HAVE_BUILTIN_FONT_MAP
	return _parseFont(el, fontmap_png, sizeof(fontmap_png));
#else
	// shouldn't get here
	return false;
#endif
}


bool FontMapLoader::loadConfig() {
	if (FontMapLoader::loaded) {
		FontMapLoader::logger.warn("Cannot reload font maps");
		return false;
	}
	FontMapLoader::loaded = true;

	string conf_fonts = Path::join(Path::dir_root, "data/conf/fonts.xml");
#if RRE_DEBUGGING
	FontMapLoader::logger.debug("Loading external fonts config: \"" + conf_fonts + "\"");
#endif
	if (!Filesystem::fexist(conf_fonts)) {
		FontMapLoader::logger.warn("Fonts config not found: \"" + conf_fonts + "\"");
		// don't close application
		return true;
	}

	XMLDocument doc;
	if (doc.LoadFile(conf_fonts.c_str()) != XML_SUCCESS) {
		string msg = "Failed to load fonts config: \"" + conf_fonts + "\"";
		FontMapLoader::logger.error(msg);
		Dialog::error(msg);
		return false;
	}

	XMLElement* root = doc.FirstChildElement("fonts");
	if (root == nullptr) {
		string msg = "Root element \"fonts\" not found: \"" + conf_fonts + "\"";
		FontMapLoader::logger.error("XML Parsing Error: " + msg);
		Dialog::error("XML Parsing Error", msg);
		return false;
	}

	XMLElement* el = root->FirstChildElement("font");
	while (el != nullptr) {
		if (!_parseFont(el, nullptr, 0)) {
			return false;
		}
		el = el->NextSiblingElement("font");
	}

	return true;
}
