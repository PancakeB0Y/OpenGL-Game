#include "Matrix4.h"
#include <math.h>

Matrix4 Matrix4::Mul(Matrix4 a, Matrix4 b) {
    Matrix4 c;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            c.a[i][j] = a.a[i][0] * b.a[0][j] + a.a[i][1] * b.a[1][j] +
                a.a[i][2] * b.a[2][j] + a.a[i][3] * b.a[3][j];
        }
    }
    return c;
}

Matrix4 Matrix4::Identity() {
    Matrix4 m;
    m.a[0][0] = 1;
    m.a[1][1] = 1;
    m.a[2][2] = 1;
    m.a[3][3] = 1;
    return m;
}

Matrix4 Matrix4::Scale(GLfloat x, GLfloat y, GLfloat z) {
    Matrix4 m;
    m.a[0][0] = x;
    m.a[1][1] = y;
    m.a[2][2] = z;
    m.a[3][3] = 1;
    return m;
}

Matrix4 Matrix4::Translation(GLfloat x, GLfloat y, GLfloat z) {
    Matrix4 m;
    m.a[0][0] = 1;
    m.a[1][1] = 1;
    m.a[2][2] = 1;
    m.a[3][3] = 1;

    m.a[0][3] = x;
    m.a[1][3] = y;
    m.a[2][3] = z;
    return m;
}

Matrix4 Matrix4::RotationX(GLfloat x) {
    Matrix4 rx;
    rx.a[0][0] = 1;
    rx.a[3][3] = 1;

    rx.a[1][1] = cos(x);
    rx.a[1][2] = -sin(x);
    rx.a[2][1] = sin(x);
    rx.a[2][2] = cos(x);

    return rx;
}

Matrix4 Matrix4::RotationY(GLfloat y) {
    Matrix4 ry;
    ry.a[1][1] = 1;
    ry.a[3][3] = 1;

    ry.a[0][0] = cos(y);
    ry.a[0][2] = sin(y);
    ry.a[2][0] = -sin(y);
    ry.a[2][2] = cos(y);

    return ry;
}

Matrix4 Matrix4::RotationZ(GLfloat z) {
    Matrix4 rz;
    rz.a[2][2] = 1;
    rz.a[3][3] = 1;

    rz.a[0][0] = cos(z);
    rz.a[0][1] = -sin(z);
    rz.a[1][0] = sin(z);
    rz.a[1][1] = cos(z);

    return rz;
}