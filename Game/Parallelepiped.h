#pragma once
#include "Model.h"

class Parallelepiped : public Model {
private:
	GLfloat w, h, d;
	int program;
	unsigned int VBO, VAO;

public:
	Parallelepiped(GLfloat w, GLfloat h, GLfloat d);
	void setup();
	void cleanup();
	void draw(Matrix4 m);
};