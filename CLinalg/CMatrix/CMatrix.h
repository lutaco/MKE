#ifndef CMATRIX_CMATRIX_H
#define CMATRIX_CMATRIX_H

#define ONES 1 // Матрица с единицами на диагонале
#define ZEROS 2 // Матрица с нулевыми элементами
#define EMPTY 3 // Мартица с неинициализированными элементами

#include <iostream>

class Matrix {
private:
    int w; // Ширина матрицы
    int h; // Высота
    double *A;  // Массив для значений
public:
    Matrix(); // Конструктор умолчания
    Matrix(int, int, int); // консруктор создает матрицу n*m вида (ONES or ZEROS or EMPY) по умолчанию вид EMPTY
    Matrix(int, int, double*); // создает матрицу n*m по массиву double. Длина массива должна быть рава nxm
    Matrix(const Matrix&); // Конструктор преобразования
    double& operator()(int, int); // Обращение к элементу матрицы. Дла матриц
    Matrix& operator=(const Matrix&); // Перегрузка оператора присваивания
    Matrix dot(const Matrix&); // Умножение матриц
    Matrix operator*(const Matrix&); // Тоже, что и dot
    Matrix operator*(double); // Умножение матрицы на число
    Matrix operator/(double); // Деление матрицы на число
    Matrix operator+(Matrix); // То же, что и add с нулевым слемещием
    Matrix operator-(Matrix); // То же, что +, только для вычитание
    Matrix refresh(int, int);
    Matrix slice(int, int, int, int);
    Matrix add(Matrix, int, int); // Добавляет к матрице другую матрицу со смещением
    Matrix transpose(); // Транспонирование матрицы
    double* get_array();
    int get_rows(); // Получить количество строк
    int get_cols(); // Получить количество столбцов
    friend std::ostream& operator<<(std::ostream& os, const Matrix& M); // Прегрузка оператора вывода
    ~Matrix(); // Деструктор класса
};

#endif //CMATRIX_CMATRIX_H