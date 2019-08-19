//
// Created by Иван Молотков on 2019-08-18.
//

#include "Solution.h"
#include "CLinalg.h"

Line::Line(double x_1, double x_2) : x1(x_1), x2(x_2) {}

double Line::len() {
    return x2 - x1;
}

Element::Element(Line line_, std::array<int, 2> nodes_) : nodes(nodes_), line(line_) {}


Solution::Solution(Fem *fem_prt, std::vector<Element> &elements) {

    size_t count_element = elements.size() + 1;
    K = Matrix (count_element, count_element, ZEROS);
    Q = Matrix (count_element, 1, ZEROS);
    D = Matrix (count_element, 1, ZEROS);

    assembly(K, elements, [fem_prt] (double len) { return fem_prt->get_k(len); });
    assembly(Q, elements, [fem_prt] (double len) { return fem_prt->get_q(len); });
    assembly(D, elements, [fem_prt] (double len) { return fem_prt->get_d(len); });

}


void Solution::assembly(Matrix &M, std::vector<Element> &elements, const std::function<Matrix(double)> &ptr_func) {

    Matrix size = (ptr_func)(elements[0].line.len());
    int cols = size.get_cols(), rows = size.get_rows();

    for (auto &element : elements) {

        Matrix local = (ptr_func)(element.line.len());

        for (int row = 0; row < rows; ++row)
            for (int col = 0; col < cols; ++col)
                M(element.nodes[row], (cols == 1) ? 0 : element.nodes[col]) += local(row, col);
    }
}


bool Solution::set_cond_type_two(int node, double value) {

    if (node > Q.get_rows())
        return false;

    if (node < 0)
        node = Q.get_rows() + node;

    Q(node, 0) -= D(node, 0) * value;

    return true;

}


bool Solution::set_cond_type_one(int node, double value) {

    if (node > Q.get_rows())
        return false;

    if (node < 0)
        node = Q.get_rows() + node;

    for (int i = 0; i < Q.get_rows(); ++i) {
        Q(i, 0) -= K(i, node) * value;
        K(i, node) = K(node, i) = 0.0;
    }

    K(node, node) = 1.0;
    Q(node, 0) = value;

    return true;

}

Matrix Solution::calculate() {
    return Linalg::simple_solve(K, Q);
}
