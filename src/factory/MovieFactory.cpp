/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <cstdint> // uint*_t

#include <pugixml.hpp>

#include "Dialog.hpp"
#include "Filesystem.hpp"
#include "Image.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "StrUtil.hpp"
#include "TextureLoader.hpp"
#include "factory/MovieFactory.hpp"

using namespace pugi;
using namespace std;


namespace MovieFactory {
	static Logger logger = Logger::getLogger("MovieFactory");
};

Movie* MovieFactory::getMovie(string id) {
	string movies_conf = Path::rabs("data/conf/movies.xml");
	if (!Filesystem::fexist(movies_conf)) {
		string msg = "Movies configuration not found: " + movies_conf;
		MovieFactory::logger.error(msg);
		Dialog::error(msg);
		return nullptr;
	}

	xml_document doc;
	if (doc.load_file(movies_conf.c_str()).status != status_ok) {
		string msg = "Failed to load movies configuration: " + movies_conf;
		MovieFactory::logger.error(msg);
		Dialog::error(msg);
		return nullptr;
	}

	xml_node root = doc.child("movies");
	if (root.type() == node_null) {
		string msg = "Root element \"movies\" not found: " + movies_conf;
		MovieFactory::logger.error("XML Parsing Error: ", msg);
		Dialog::error("XML Parsing Error", msg);
		return nullptr;
	}

	xml_node movie_el = root.child("movie");
	while (movie_el.type() != node_null) {
		xml_attribute id_attr = movie_el.attribute("id");
		if (id_attr.empty()) {
			string msg = "Missing attribute \"id\" in movie tag: " + movies_conf;
			MovieFactory::logger.error("XML Parsing Error: ", msg);
			Dialog::error("XML Parsing Error", msg);
			return nullptr;
		}
		if (id.compare(id_attr.value()) == 0) {
			break;
		}

		movie_el = movie_el.next_sibling("movie");
	}

	MovieFrameList frames;
	//vector<pair<uint16_t, Sprite*>> text_sprites;
	vector<string> texts;

	if (movie_el.type() != node_null) {
		xml_node frame_el = movie_el.child("frame");
		while (frame_el.type() != node_null) {
			xml_attribute ms_attr = frame_el.attribute("ms");
			if (ms_attr.empty()) {
				string msg = "Frame tag without \"ms\" attribute: "
						+ movies_conf;
				MovieFactory::logger.error("XML Parsing Error: ", msg);
				Dialog::error("XML Parsing Error", msg);
				return nullptr;
			}
			uint32_t duration = 0;
			StrUtil::parseUInt(duration, ms_attr.value());
			string frame_id = frame_el.text().get();
			Image* img = new Image(TextureLoader::load(Path::join("movie", frame_id)));
			if (!img->ready()) {
				string msg = "Failed to load movie frame image \"" + frame_id
						+ "\": " + movies_conf;
				MovieFactory::logger.error(msg);
				Dialog::error(msg);
				return nullptr;
			}
			frames.push_back({duration, img});

			frame_el = frame_el.next_sibling("frame");
		}

		xml_node text_el = movie_el.child("text");
		while (text_el.type() != node_null) {
			string text = text_el.text().get();

			// TODO: support delay & duration

			xml_attribute delay_attr = text_el.attribute("delay");
			// FIXME: should this be uint32_t?
			uint16_t delay = 0;
			StrUtil::parseUShort(delay, delay_attr.value());

			xml_attribute duration_attr = text_el.attribute("duration");
			// FIXME: should this be uint32_t?
			uint16_t duration = 0;
			StrUtil::parseUShort(duration, duration_attr.value());

			texts.push_back(text);

			text_el = text_el.next_sibling("text");
		}
	}

	if (frames.size() == 0) {
		string msg = "Movie \"" + id + "\" has no frames configured: "
				+ movies_conf;
		MovieFactory::logger.error(msg);
		Dialog::error(msg);
		return nullptr;
	}

	Movie* movie = new Movie(frames);
	for (string t: texts) {
		movie->addText(t);
	}

	return movie;
}
