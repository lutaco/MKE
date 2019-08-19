#include <iostream>
#include <cstring>
#include <cmath>
#include "CMatrix.h"

Matrix::Matrix() {
	w = h = 0;
	A = nullptr;
};

Matrix Matrix::refresh(int k, int max) {
		Matrix M(*this);
		double p[h];
		memcpy(p, M.A + (k * h), sizeof(double) * h);
		memcpy(M.A + (k * h), M.A + (max * h), sizeof(double) * h);
		memcpy(M.A + (max * h), p, sizeof(double) * h);
		return M;
};

double* Matrix::get_array() {
	double* res = new double[h * w];
	memcpy(res, A, sizeof(double) * w * h);
	return res;
}

Matrix::Matrix(int rows, int columns, int type = EMPTY) : h(rows), w(columns) { 
	A = new double[w * h];

	if (type == EMPTY)
		return;

	memset(A, 0.0, sizeof(double) * w * h);
	if (type == ONES)
		for (int i = 0; i < h; i++)
			A[w * i + i] = 1.0;
};

Matrix::Matrix(int rows, int columns, double* M) : h(rows), w(columns) { 
	A = new double[w * h];
	memcpy(A, M, sizeof(double) * w * h);
};

double& Matrix::operator()(int row, int column = 0) {
	if (column == 0 &&  h == 1)
		return A[row];
	return A[w * row + column];
};

Matrix::Matrix(const Matrix& M) {
	w = M.w;
	h = M.h;
	A = new double[w * h];
	memcpy(A, M.A, sizeof(double) * w * h);
};

Matrix& Matrix::operator=(const Matrix& M) {
	delete [] A;
	w = M.w;
	h = M.h;
	A = new double[w * h];
	memcpy(A, M.A, sizeof(double) * w * h);
	return *this;
};

Matrix Matrix::dot(const Matrix& B) {
	
	if (w != B.h) {
		std::cerr << "ooops" << std::endl;
		exit(-1);
	}

	Matrix C(h, B.w, ZEROS);

	double *pa = A, *pb = B.A, *pm = C.A, *pc;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			pc = pm;
			for (int k = 0; k < B.w; k++) 
				*pc++ += (*pa) * (*pb++);
			pa++;
		}
		pb = B.A;
		pm = pc;
	}

	return C;
};

Matrix Matrix::operator*(const Matrix& B) {
	return this->dot(B);
};

Matrix Matrix::operator*(double num) {
	Matrix C(*this);
	for (int i = 0; i < h * w; i++)
		C.A[i] *= num;
	return C;
};

Matrix Matrix::operator/(double num) {
	return Matrix(*this) * (1.0 / num);
};

Matrix Matrix::add(Matrix M, int h_s = 0, int w_s = 0) {

	if (h < M.h + h_s || w < M.w + w_s) {
		Matrix T(M.h + h_s, M.w + w_s, ZEROS);
		T = T.add(M, h_s, w_s).add(*this);
		return T;
	}
		
	Matrix T = *this;
	for (int i = 0; i < M.h; i++)
		for(int j = 0; j < M.w; j++)
			T(i + h_s, j + w_s) += M(i, j);

	return T;

};

Matrix Matrix::operator+(Matrix B) {
	return Matrix(*this).add(B);
};

Matrix Matrix::operator-(Matrix B) {
	return Matrix(*this).add(B * -1.0);
};

Matrix Matrix::transpose() {
	Matrix T(w, h);
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			T(j, i) = this->operator()(i, j);
	return T;
};	


std::ostream& operator<<(std::ostream& os, const Matrix& M)  {
	os << std::endl;
		os << "Matrix " << M.h << "x" << M.w << std::endl;
		for (int i = 0; i < M.h; i++) {
			for (int j = 0; j < M.w; j++)
					os << M.A[M.w * i + j] << " " ;
			os << std::endl;
		}
	return os;
};

Matrix Matrix::slice(int y0, int y1, int x0 = 0, int x1 = 0) {

	if (x0 == 0 && x1 == 0) {
		Matrix T;
		if (h == 1)
			T = Matrix(1, y1 - y0);
		else
			T = Matrix(y1 - y0, 1);
		memcpy(T.A, A + y0, sizeof(double) * y1 - y0);
		return T;	
	}

	int w_t = x1 - x0;
	int h_t = y1 - y0;
	Matrix T(h_t, w_t);

	for (int i = 0; i < h_t; ++i) 
		memcpy(T.A + w_t * i, A + w * (y0 + i) + x0, sizeof(double) * w_t);

	return T;
};	


int Matrix::get_rows() { return h; };


int Matrix::get_cols() { return w; };


Matrix::~Matrix() { delete []A; };
