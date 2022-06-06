#pragma once
#include "Matrix4.h"

class Model {
public:
	virtual void setup() = 0;
	virtual void cleanup() = 0;
	virtual void draw(Matrix4 m) = 0;
};