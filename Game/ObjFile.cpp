#include "ObjFile.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void ObjFile::load(string filename) {
	ifstream myfile("C:/Users/A3/projects/game/Game/models/" + filename);
	string mystring;

	while (!myfile.eof()) {
		char c = myfile.get();
		if (c < 0) break;
		if (c == 'v') {
			c = myfile.get();
			if (c == 'n') {
				double x, y, z;
				myfile >> x >> y >> z;
				double l = sqrt(x * x + y * y + z * z);
				x /= l; y /= l; z /= l;
				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(z);
			}
			else if (c == 't') {
				double x, y;
				myfile >> x >> y;
				texCoords.push_back(x);
				texCoords.push_back(y);
			}
			else if (c == ' ') {
				double x, y, z;
				myfile >> x >> y >> z;
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
		}
		
		else if (c == 'f') {
			for (int i = 0; i < 3; i++) {
				GLushort vi = 0;
				GLushort vi2 = 0;
				GLushort vi3 = 0;
				GLushort indexN = 0;
				while (true) {
					c = myfile.get();
					if (c != ' ') break;
				}
				while (true) {
					if ((c >= '0') && (c <= '9')) {
						if (indexN == 0) {
							vi = vi * 10 + (c - '0');
						}
						else if (indexN == 1) {
							vi2 = vi2 * 10 + (c - '0');
						}
						else if (indexN == 2) {
							vi3 = vi3 * 10 + (c - '0');
						}
						
					}
					else if (c == '/') {
						indexN++;
					}
					else break;
					c = myfile.get();
				}
				while ((c != ' ') && (c != '\r') && (c != '\n')) {
					c = myfile.get();
				}
				indexes.push_back(vi - 1);
				indexesT.push_back(vi2 - 1);
				indexesN.push_back(vi3 - 1);
			}
		}

		while ((c > 0) && (c != '\r') && (c != '\n')) {
			c = myfile.get();
		}
	}
	myfile.close();

	for (int i = 0; i < indexes.size(); i++) {
		for (int j = 0; j < 3; j++) {
			data.push_back(vertices[indexes[i] * 3 + j]);
		}
		for (int j = 0; j < 3; j++) {
			data.push_back(normals[indexesN[i] * 3 + j]);
		}
		for (int j = 0; j < 2; j++) {
			data.push_back(texCoords[indexesT[i] * 2 + j]);
		}
	}

}



