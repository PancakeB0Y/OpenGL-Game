#pragma once
#include <glad/glad.h>

class Matrix4 {
public:
    GLfloat a[4][4] = { {0} };

    static Matrix4 Mul(Matrix4 a, Matrix4 b);

    static Matrix4 Identity();

    static Matrix4 Scale(GLfloat x, GLfloat y, GLfloat z);

    static Matrix4 Translation(GLfloat x, GLfloat y, GLfloat z);

    static Matrix4 RotationX(GLfloat x);
    static Matrix4 RotationY(GLfloat y);
    static Matrix4 RotationZ(GLfloat z);
};