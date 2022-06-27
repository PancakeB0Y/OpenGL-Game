#pragma once
#include "Matrix4.h"

class TriangleProcessor {
public:
	virtual void process(double p0[3], double p1[3], double p2[3]) = 0;
};

class Model {
public:
	virtual void setup() = 0;
	virtual void cleanup() = 0;
	virtual void draw(Matrix4 m) = 0;
	virtual void processTriangles(TriangleProcessor *processor, Matrix4 m) = 0;

};