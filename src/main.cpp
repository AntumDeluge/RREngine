/* Copyright © 2018-2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 *
 * WARNING: This software is in planning stages & is not ready
 * for regular use.
 */

#include <iostream>
#include <string>
#include <tinyxml2.h>

#include "config.h"

#include "fileio.h"
#include "paths.h"
#include "reso.h"
#include "singletons.h"

using namespace std;


const string ver = to_string(RREngine_VER_MAJ) + "." + to_string(RREngine_VER_MIN) + "." + to_string(RREngine_VER_REL); // @suppress("Invalid arguments") @suppress("Symbol is not resolved")

void showVersion();

int main(int argc, char** argv) {
	// change to executable directory
	changeDir(dir_root);

	string title = "R&R Engine";
	// default dimensions
	int width = RES1.first;
	int height = RES1.second;

	string game_conf = concatPath(dir_root, "data/conf/game.xml");

	if (fileExists(game_conf)) {
		tinyxml2::XMLDocument doc;
		doc.LoadFile(game_conf.c_str());
		tinyxml2::XMLElement* root = doc.RootElement();

		tinyxml2::XMLElement* name_element = root->FirstChildElement("name");
		if (name_element != NULL) {
			title = name_element->GetText();
		}

		const tinyxml2::XMLAttribute* wAttribute;
		const tinyxml2::XMLAttribute* hAttribute;
		tinyxml2::XMLElement* resElement = root->FirstChildElement("res");
		if (resElement != NULL) {
			wAttribute = resElement->FindAttribute("w");
			hAttribute = resElement->FindAttribute("h");
		}

		if (wAttribute != NULL && hAttribute != NULL) {
			width = wAttribute->IntValue();
			height = hAttribute->IntValue();
		}
	}

	return GetGameWindow()->init(title, width, height);
}


void showVersion() {
	cout << "Version: " << ver << endl;
}
