/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <cstddef> // size_t
#include <cstdint> // *int*_t
#include <string>
#include <unordered_map>
#include <vector>

#include <pugixml.hpp>

#include "Dialog.hpp"
#include "Filesystem.hpp"
#include "FontMap.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "StrUtil.hpp"
#include "TextureLoader.hpp"
#include "builtin/conf/fonts.h"
#if HAVE_BUILTIN_FONT_MAP
#include "builtin/tileset/fontmap_png.h"
#endif
#include "factory/FontMapFactory.hpp"
#include "store/FontMapStore.hpp"

using namespace pugi;
using namespace std;


namespace FontMapFactory {
	/** Logger instance dedicated to namespace. */
	Logger logger = Logger::getLogger("FontMapFactory");

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
unordered_map<wchar_t, int32_t> _parseCharacters(xml_node el) {
	unordered_map<wchar_t, int32_t> empty_map;
	unordered_map<wchar_t, int32_t> char_map;

	xml_node cel = el.child("char");
	while (cel.type() != node_null) {
		xml_attribute attr = cel.attribute("index");
		if (attr.empty()) {
			string msg = "Missing attribute \"index\" in XML element \"char\"";
			FontMapFactory::logger.error("XML Parsing Error: ", msg);
			Dialog::error("XML Parsing Error", msg);
			return empty_map;
		}

		const int start_index = StrUtil::toInt(attr.value());
		const string value = cel.text().get();
		for (int idx = 0; idx < value.length(); idx++) {
			int index_offset = start_index + idx;
			wchar_t c = value[idx];
			char_map[c] = index_offset;
		}

		cel = cel.next_sibling("char");
	}

	if (char_map.size() == 0) {
		string msg = "No character mappings defined";
		FontMapFactory::logger.error("XML Parsing Error: ", msg);
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
bool _parseFont(xml_node el, const uint8_t data[], const uint32_t data_size) {
	vector<string> err;

	string id = "";
	string rpath = "";
	int w = 0;
	int h = 0;

	xml_attribute attr = el.attribute("id");
	if (attr.empty()) {
		err.push_back("Missing font attribute \"id\"");
	} else {
		id = attr.value();
	}

	attr = el.attribute("tileset");
	if (attr.empty()) {
		err.push_back("Missing font attribute \"tileset\"");
	} else {
		rpath = Path::join("tileset", attr.value());
	}

	attr = el.attribute("w");
	if (attr.empty()) {
		err.push_back("Missing font attribute \"w\"");
	} else {
		w = StrUtil::toInt(attr.value());
	}

	attr = el.attribute("h");
	if (attr.empty()) {
		err.push_back("Missing font attribute \"h\"");
	} else {
		h = StrUtil::toInt(attr.value());
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
		FontMapFactory::logger.error("XML Parsing Errors: ", msg);
		Dialog::error("XML Parsing Errors", msg);
		return false;
	}

	unordered_map<wchar_t, int> char_map = _parseCharacters(el);
	if (char_map.size() == 0) {
		return false;
	}

	// add parsed data to font store
	if (data != nullptr) {
		FontMapStore::add(id, new FontMap(TextureLoader::loadFM(data, data_size), char_map, w, h));
	} else {
		FontMapStore::add(id, new FontMap(TextureLoader::load(rpath), char_map, w, h));
	}

	return true;
}


bool FontMapFactory::loadBuiltin() {
#if RRE_DEBUGGING
	FontMapFactory::logger.debug("Loading built-in fonts config");
#endif

	xml_document doc;
	if (doc.load_string(builtin_fonts_config.c_str()).status != status_ok) {
		string msg = "Failed to load built-in fonts config";
		FontMapFactory::logger.error(msg);
		Dialog::error(msg);
		return false;
	}

	xml_node root = doc.child("fonts");
	if (root.type() == node_null) {
		string msg = "Root element \"fonts\" not found";
		FontMapFactory::logger.error("XML Parsing Error: ", msg);
		Dialog::error("XML Parsing Error", msg);
		return false;
	}

	xml_node el = root.child("font");
	if (el.type() == node_null) {
		string msg = "Built-in font not configured";
		FontMapFactory::logger.error("XML Parsing Error: ", msg);
		Dialog::error("XML Parsing Error", msg);
		return false;
	}

#if HAVE_BUILTIN_FONT_MAP
	return _parseFont(el, fontmap_png, (uint32_t) sizeof(fontmap_png));
#else
	// shouldn't get here
	return false;
#endif
}


bool FontMapFactory::loadConfig() {
	if (FontMapFactory::loaded) {
		FontMapFactory::logger.warn("Cannot reload font maps");
		return false;
	}
	FontMapFactory::loaded = true;

	string conf_fonts = Path::join(Path::dir_root, "data/conf/fonts.xml");
#if RRE_DEBUGGING
	FontMapFactory::logger.debug("Loading external fonts config: \"", conf_fonts, "\"");
#endif
	if (!Filesystem::fexist(conf_fonts)) {
		FontMapFactory::logger.warn("Fonts config not found: \"", conf_fonts, "\"");
		// don't close application
		return true;
	}

	xml_document doc;
	if (doc.load_file(conf_fonts.c_str()).status != status_ok) {
		string msg = "Failed to load fonts config: \"" + conf_fonts + "\"";
		FontMapFactory::logger.error(msg);
		Dialog::error(msg);
		return false;
	}

	xml_node root = doc.child("fonts");
	if (root.type() == node_null) {
		string msg = "Root element \"fonts\" not found: \"" + conf_fonts + "\"";
		FontMapFactory::logger.error("XML Parsing Error: ", msg);
		Dialog::error("XML Parsing Error", msg);
		return false;
	}

	xml_node el = root.child("font");
	while (el.type() != node_null) {
		if (!_parseFont(el, nullptr, 0)) {
			return false;
		}
		el = el.next_sibling("font");
	}

	return true;
}
