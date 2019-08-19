//
// Created by Иван Молотков on 2019-08-18.
//

#ifndef MKE_SOLUTION_H
#define MKE_SOLUTION_H

#include "CMatrix.h"
#include <array>
#include <vector>

class Line {
public:
    double x1;
    double x2;
    Line(double, double);
    double len();
};

class Element {
public:
    Line line;
    std::array<int, 2> nodes;
    Element(Line, std::array<int, 2>);
};

class Fem {
public:
    virtual Matrix get_k(double) = 0;
    virtual Matrix get_q(double) = 0;
    virtual Matrix get_d(double) = 0;
    virtual ~Fem() = default;
};

class Solution {
    Matrix K;
    Matrix Q;
    Matrix D;
public:
    Solution(Fem *, std::vector<Element> &);
    static void assembly(Matrix &, std::vector<Element> &, const std::function<Matrix(double)> &);
    bool set_cond_type_one(int, double);
    bool set_cond_type_two(int, double);
    Matrix calculate();
};


#endif //MKE_SOLUTION_H
