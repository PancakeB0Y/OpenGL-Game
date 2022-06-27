#include "Matrix4.h"
#include <GLFW/glfw3.h>
#include <math.h>

const GLfloat epsilon = 0.00005;

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

Matrix4 Matrix4::Scale(double x, double y, double z) {
    Matrix4 m;
    m.a[0][0] = x;
    m.a[1][1] = y;
    m.a[2][2] = z;
    m.a[3][3] = 1;
    return m;
}

Matrix4 Matrix4::Translation(double x, double y, double z) {
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

Matrix4 Matrix4::Projection(double w, double h, double a, double nearPlane, double farPlane) {
    Matrix4 m;

    m.a[0][0] = h/w;
    m.a[1][1] = 1;
    m.a[2][2] = 1 / (farPlane - nearPlane);
    m.a[2][3] = -nearPlane * m.a[2][2];
    m.a[3][2] = (cos(a/2)/sin(a/2));

    return m;
}

Matrix4 Matrix4::RotationX(double x) {
    Matrix4 rx;
    rx.a[0][0] = 1;
    rx.a[3][3] = 1;

    rx.a[1][1] = cos(x);
    rx.a[1][2] = -sin(x);
    rx.a[2][1] = sin(x);
    rx.a[2][2] = cos(x);

    return rx;
}

Matrix4 Matrix4::RotationY(double y) {
    Matrix4 ry;
    ry.a[1][1] = 1;
    ry.a[3][3] = 1;

    ry.a[0][0] = cos(y);
    ry.a[0][2] = sin(y);
    ry.a[2][0] = -sin(y);
    ry.a[2][2] = cos(y);

    return ry;
}

Matrix4 Matrix4::RotationZ(double z) {
    Matrix4 rz;
    rz.a[2][2] = 1;
    rz.a[3][3] = 1;

    rz.a[0][0] = cos(z);
    rz.a[0][1] = -sin(z);
    rz.a[1][0] = sin(z);
    rz.a[1][1] = cos(z);

    return rz;
}

Matrix4 Matrix4::Invert() {
    Matrix4 t = *this;
    Matrix4 e = Matrix4::Identity();
    
    for (int f = 0; f < 4; f++) {
        if (fabs(t.a[f][f]) < epsilon) {
            int max = fabs(t.a[f][f]);
            int n = f;
            for (int i = f+1; i < 4; i++) {
                if (fabs(t.a[i][f]) > max) {
                    max = fabs(t.a[i][f]);
                    n = i;
                }
            }
            for (int i = 0; i < 4; i++) {
                t.a[f][i] += t.a[n][i];
                e.a[f][i] += e.a[n][i];
            }
        }

        if (fabs(t.a[f][f]) < epsilon) return Matrix4::Identity();

        double d = t.a[f][f];

        for (int i = 0; i < 4; i++) {
            t.a[f][i] /= d;
            e.a[f][i] /= d;
        }

        for (int i = f+1; i < 4; i++) {
            if (fabs(t.a[i][f]) >= epsilon) {
                double negative = -(1.0f / t.a[i][f]);
                for (int j = 0; j < 4; j++) {
                    t.a[i][j] *= negative;
                    e.a[i][j] *= negative;
                    t.a[i][j] += t.a[f][j];
                    e.a[i][j] += e.a[f][j];
                }
            }
        }
    }

    for (int f = 3; f >= 0; f--) {
        double d = t.a[f][f];

        for (int i = f - 1; i >= 0; i--) {
            if (fabs(t.a[i][f]) >= epsilon) {
                double negative = -t.a[i][f];
                for (int j = 0; j < 4; j++) {
                    t.a[i][j] += t.a[f][j] * negative;
                    e.a[i][j] += e.a[f][j] * negative;
                }
            }
        }
    }

    return e;
}

GLfloat* Matrix4::getFloatMatirx() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            b[i][j] = a[i][j];
        }
    }
    return (GLfloat*)b;
}

void Matrix4::TransformInPlace(double p[3]) {
    double x = a[0][0] * p[0] + a[0][1] * p[1] + a[0][2] * p[2] + a[0][3];
    double y = a[1][0] * p[0] + a[1][1] * p[1] + a[1][2] * p[2] + a[1][3];
    double z = a[2][0] * p[0] + a[2][1] * p[1] + a[2][2] * p[2] + a[2][3];
    p[0] = x;
    p[1] = y;
    p[2] = z;
}