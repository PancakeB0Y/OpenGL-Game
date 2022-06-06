#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>

using namespace std;

class ObjFile {
public:
	vector<GLfloat> data;
	vector<GLfloat> vertices;
	vector<GLfloat> normals;
	vector<GLfloat> texCoords;
	vector<GLushort> indexes;
	vector<GLushort> indexesN;
	vector<GLushort> indexesT;

	void load(string filename);
};