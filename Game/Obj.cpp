#include "Matrix4.h"
#include "Obj.h"
#include <vector>
#include <iostream>
using namespace std;

Obj::Obj(Model* model, Matrix4 transform) {
	this->model = model;
	this->transform = transform;
}

void Obj::draw(Matrix4 m) {
	Matrix4 tm = Matrix4::Mul(m, transform);
	if(model) model->draw(tm);
	for (int i = 0; i < children.size(); i++) {
		children[i]->draw(tm);
	}
}

void Obj::addChild(Obj* child) {
	children.push_back(child);
}

void Obj::setTransform(Matrix4 transform) {
	this->transform = transform;
}

Matrix4 Obj::getTranform() {
	return transform;
}