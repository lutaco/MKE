#include "CLinalg.h"
#include "CMatrix.h"
#include <iostream>

Matrix Linalg::simple_solve(Matrix &mA, Matrix &mb) {
    if (mA.get_cols() != mA.get_rows() != mb.get_rows() && mb.get_cols() != 1) {
        std::cerr << "ooops" << std::endl;
        exit(-1);
    }

    int n = mA.get_cols();
    double* A = mA.get_array();
    double* b = mb.get_array();

    for (int i = 0; i < n - 1; ++i) {
        for (int row = i + 1; row < n; ++row) {
            double div_row = A[row * n + i] / A[i * n + i];
            for (int col = i; col < n; ++col) {
                A[row * n + col] -= A[i * n + col] * div_row;
            }
            b[row] -= b[i] * div_row;
        }
    }

    for (int row = n - 1; row >= 0; --row) {
        for (int col = row + 1; col < n; ++col) {
            b[row] -= A[row * n + col] * b[col];
        }
        b[row] /= A[row * n + row];
    }

    return Matrix(n, 1, b);
};
