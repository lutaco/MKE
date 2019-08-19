#include <iostream>//заголовок потоков ввода-вывода
#include <vector>
#include <array>
#include <cmath>
#include "headers.h"

using namespace std; //разрешить доступ к стандартному пространству имен


class FemLinear : public Fem {
public:

    Matrix get_k(double L) override {

        Matrix K(2, 2, ZEROS);

        K(0, 0) = -3 / L - 10 * L / 6;
        K(0, 1) = 3 / L - 5 * L / 6;
        K(1, 0) = 3 / L - 5 * L / 6;
        K(1, 1) = -3 / L - 10 * L / 6;

        return K;
    };

    Matrix get_q(double L) override {

        Matrix Q(2, 1, EMPTY);

        Q(0, 0) = -L / 2;
        Q(1, 0) = -L / 2;

        return Q;
    };

    Matrix get_d(double L) override {

        Matrix D(2, 1, EMPTY);

        D(0, 0) = - 3;
        D(1, 0) = + 3;

        return D;
    }
};


class FemQuadro : public Fem {

    Matrix get_k(double L) override {

        Matrix K(2, 2, ZEROS);

        K(0, 0) = - (5 * pow(L, 4) / 8 + 13 * pow(L, 2) + 18) / (L * (pow(L, 2) + 6));
        K(0, 1) = + (5 * pow(L, 4) / 24 - 2 * pow(L, 2) + 18) / (L * (pow(L, 2) + 6));
        K(1, 0) = + (5 * pow(L, 4) / 24 - 2 * pow(L, 2) + 18) / (L * (pow(L, 2) + 6));
        K(1, 1) = - (5 * pow(L, 4) / 8 + 13 * pow(L, 2) + 18) / (L * (pow(L, 2) + 6));

        return K;
    };

    Matrix get_q(double L) override {

        Matrix Q(2, 1, EMPTY);

        Q(0, 0) = - L / 6 + (2 * L * (L / 3 - 8 / L)) / (3 * (8 * L / 3 + 16 / L));
        Q(1, 0) = - L / 6 + (2 * L * (L / 3 - 8 / L)) / (3 * (8 * L / 3 + 16 / L));

        return Q;
    };

    Matrix get_d(double L) override {

        Matrix D(2, 1, EMPTY);

        D(0, 0) = - 2;
        D(1, 0) = + 2;

        return D;
    }
};


//double f_x(double x) {
//    return
//            exp(-sqrt(5.0 / 3.0) * x)
//            * (exp(sqrt(5.0 / 3.0) * x) - 1.0)
//            * (exp(sqrt(5.0 / 3.0) * x) + 49.0 * exp(sqrt(5.0 / 3.0) * (x + 12.0))
//               + 49.0 * exp(4.0 * sqrt(15.0)) + exp(8.0 * sqrt(15.0))
//            )
//            / (5.0 * (exp(8.0 * sqrt(15)) - 1.0));
//}


vector<double> get_x_uniform(double left, double right, int n) {

    double step = (right - left) / (n - 1);
    vector<double> res;
    res.push_back(left);

    while (--n) {
        res.push_back(left + step + res.back());
    }

    return res;
}


vector<Element> get_element_by_x(vector<double> const &x_vector) {

    vector<Element> res;
    for (size_t i = 0; i < x_vector.size() - 1; ++i) {
        res.emplace_back(Element( Line(x_vector[i], x_vector[i + 1]), array<int, 2>({int(i), int(i + 1)}) ));
    }

    return res;
}

int main() {

    auto x = get_x_uniform(0.0, 12.0, 20);
    auto elements = get_element_by_x(x);

    Solution solution(new FemLinear, elements);

    solution.set_cond_type_one(-1, 10);
    solution.set_cond_type_two(0, 10);

    cout << solution.calculate().transpose() << endl;

    return 0;
}