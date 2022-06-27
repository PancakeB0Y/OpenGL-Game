#pragma once
#include "Model.h"

class Parallelepiped : public Model {
private:
	GLfloat vertices[216];
	GLfloat w, h, d;
	int program;
	unsigned int VBO = 0, VAO = 0;

public:
	Parallelepiped(GLfloat w, GLfloat h, GLfloat d);
	void setup();
	void cleanup();
	void draw(Matrix4 m);
	void processTriangles(TriangleProcessor* processor, Matrix4 m);
};