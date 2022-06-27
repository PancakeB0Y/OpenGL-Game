#pragma once
#include <glad/glad.h>

class Matrix4 {
public:
    double a[4][4] = { {0} };
    GLfloat b[4][4] = { {0} };

    static Matrix4 Mul(Matrix4 a, Matrix4 b);

    static Matrix4 Identity();

    static Matrix4 Scale(double x, double y, double z);

    static Matrix4 Translation(double x, double y, double z);
    
    static Matrix4 Projection(double w, double h, double a, double nearPlane, double farPlane);

    static Matrix4 RotationX(double x);
    static Matrix4 RotationY(double y);
    static Matrix4 RotationZ(double z);
    Matrix4 Invert();

    GLfloat* getFloatMatirx();

    void TransformInPlace(double p[3]);
};
