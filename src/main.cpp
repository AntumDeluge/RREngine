/* Copyright © 2018 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 *
 * WARNING: This software is in planning stages & is not ready
 * for regular use.
 */

#include <iostream>
#include <string>
using namespace std;

#include "config.h"


const string ver = to_string(RREngine_VER_MAJ) + "." + to_string(RREngine_VER_MIN) + "." + to_string(RREngine_VER_REL);

void showVersion();

int main(int argc, char** argv) {
	showVersion();

	return 0;
}


void showVersion() {
	cout << "Version: " << ver << endl;
}
