#include "Calculate.h"
#include <math.h>

const double epsilon = 0.00005;

bool Calculate::calcEq(double equation[3][4]) {
    for (int f = 0; f < 3; f++) {
        if (fabs(equation[f][f]) < epsilon) {
            double max = fabs(equation[f][f]);
            int n = f;
            for (int i = f + 1; i < 3; i++) {
                if (fabs(equation[i][f]) > max) {
                    max = fabs(equation[i][f]);
                    n = i;
                }
            }
            for (int i = 0; i < 4; i++) {
                equation[f][i] += equation[n][i];
            }
        }

        if (fabs(equation[f][f]) < epsilon) return false;

        double d = equation[f][f];

        for (int i = 0; i < 4; i++) {
            equation[f][i] /= d;
        }

        for (int i = f + 1; i < 3; i++) {
            if (fabs(equation[i][f]) >= epsilon) {
                double negative = -(1.0f / equation[i][f]);
                for (int j = 0; j < 4; j++) {
                    equation[i][j] *= negative;
                    equation[i][j] += equation[f][j];
                }
            }
        }

    }

    for (int f = 2; f >= 0; f--) {
        double d = equation[f][f];

        for (int i = f - 1; i >= 0; i--) {
            if (fabs(equation[i][f]) >= epsilon) {
                double negative = -equation[i][f];
                for (int j = 0; j < 4; j++) {
                    equation[i][j] += equation[f][j] * negative;
                }
            }
        }
    }

    return true;
}