#pragma once
#include "Model.h"
#include "ObjFile.h"
#include <string>

class ObjFileModel : public Model {
private:
	ObjFile file;
	string filename;
	int program;
	unsigned int VBO, VAO, EBO;

public:
	ObjFileModel(string filename);
	void setup();
	void cleanup();
	void draw(Matrix4 m);
}; 
