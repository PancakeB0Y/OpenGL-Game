#include <iostream>
#include <fstream>
#include <string>
using namespace std;

static int readFile() {
	ifstream myfile ("C:/Users/A3/projects/game/Game/models/door.obj");
	string mystring;

	while (!myfile.eof()) {
		char c = myfile.get();
		if (c == 'v') {
			double x, y, z;
			myfile >> x >> y >> z;
			cout << "V" << x << y << z << endl;

		}
		while ((c != '\r') && (c != '\n') && (!myfile.eof())) {
			c = myfile.get();
		}
	}

    return 0;
}