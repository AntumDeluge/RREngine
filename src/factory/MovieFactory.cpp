/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <cstdint> // uint*_t
#include <tinyxml2.h>

#include "Dialog.hpp"
#include "Filesystem.hpp"
#include "Image.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "TextureLoader.hpp"
#include "factory/MovieFactory.hpp"

using namespace std;
using namespace tinyxml2;


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

	XMLDocument doc;
	if (doc.LoadFile(movies_conf.c_str()) != XML_SUCCESS) {
		string msg = "Failed to load movies configuration: " + movies_conf;
		MovieFactory::logger.error(msg);
		Dialog::error(msg);
		return nullptr;
	}

	XMLElement* root = doc.FirstChildElement("movies");
	if (root == nullptr) {
		string msg = "Root element \"movies\" not found: " + movies_conf;
		MovieFactory::logger.error("XML Parsing Error: " + msg);
		Dialog::error("XML Parsing Error", msg);
		return nullptr;
	}

	XMLElement* movie_el = root->FirstChildElement("movie");
	while (movie_el != nullptr) {
		const XMLAttribute* id_attr = movie_el->FindAttribute("id");
		if (id_attr == nullptr) {
			string msg = "Missing attribute \"id\" in movie tag: " + movies_conf;
			MovieFactory::logger.error("XML Parsing Error: " + msg);
			Dialog::error("XML Parsing Error", msg);
			return nullptr;
		}
		if (id.compare(id_attr->Value()) == 0) {
			break;
		}

		movie_el = movie_el->NextSiblingElement("movie");
	}

	MovieFrameList frames;
	//vector<pair<uint16_t, Sprite*>> text_sprites;
	vector<string> texts;

	if (movie_el != nullptr) {
		XMLElement* frame_el = movie_el->FirstChildElement("frame");
		while (frame_el != nullptr) {
			const XMLAttribute* ms_attr = frame_el->FindAttribute("ms");
			if (ms_attr == nullptr) {
				string msg = "Frame tag without \"ms\" attribute: "
						+ movies_conf;
				MovieFactory::logger.error("XML Parsing Error: " + msg);
				Dialog::error("XML Parsing Error", msg);
				return nullptr;
			}
			uint32_t duration = ms_attr->UnsignedValue();
			string frame_id = frame_el->GetText();
			Image* img = new Image(TextureLoader::load(Path::join("movie", frame_id)));
			if (!img->ready()) {
				string msg = "Failed to load movie frame image \"" + frame_id
						+ "\": " + movies_conf;
				MovieFactory::logger.error(msg);
				Dialog::error(msg);
				return nullptr;
			}
			frames.push_back({duration, img});

			frame_el = frame_el->NextSiblingElement("frame");
		}

		XMLElement* text_el = movie_el->FirstChildElement("text");
		while (text_el != nullptr) {
			string text = text_el->GetText();

			// TODO: support delay & duration

			const XMLAttribute* delay_attr = text_el->FindAttribute("delay");
			uint16_t delay = delay_attr != nullptr ? delay_attr->UnsignedValue()
					: 0;

			const XMLAttribute* duration_attr = text_el->FindAttribute("duration");
			uint16_t duration = duration_attr != nullptr
					? duration_attr->UnsignedValue() : 0;

			texts.push_back(text);

			text_el = text_el->NextSiblingElement("text");
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
