#pragma once
#include "Matrix4.h"
#include "Model.h"
#include <vector>
using namespace std;


class Obj {
private:
	Model* model;
	Matrix4 transform;
	vector<Obj*> children;

public:
	Obj(Model *model, Matrix4 transform);

	void draw(Matrix4 m);

	void addChild(Obj* child);

	void setTransform(Matrix4 transform);

	Matrix4 getTranform();
};