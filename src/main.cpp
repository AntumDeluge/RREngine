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
using namespace std;

#include "config.h"

#include "fileio.h"
#include "frame.h"
#include "paths.h"
#include "reso.h"


const string ver = to_string(RREngine_VER_MAJ) + "." + to_string(RREngine_VER_MIN) + "." + to_string(RREngine_VER_REL); // @suppress("Invalid arguments") @suppress("Symbol is not resolved")

void showVersion();

int main(int argc, char** argv) {
	// FIXME: segmentation fault
	//string absolute = getThisPath();

	// default dimensions
	int width = RES1.first;
	int height = RES1.second;

	string game_conf = concatPath(dir_root, "data/conf/game.xml");

	if (fileExists(game_conf)) {
		tinyxml2::XMLDocument doc;
		doc.LoadFile("../data/conf/game.xml");
		tinyxml2::XMLElement* root = doc.RootElement();

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

	GameWindow* frame = GameWindow::get();
	return frame->init(width, height);
}


void showVersion() {
	cout << "Version: " << ver << endl;
}
