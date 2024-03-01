//
// Created by Artem Malko on 18.02.2024.
//

#ifndef FINITE_HOMOLOGIES_MATRIX_H
#define FINITE_HOMOLOGIES_MATRIX_H

#pragma once

#include <vector>


class Matrix {
public:
    std::size_t h, w;
    std::vector<std::vector<int>> body;

    Matrix() {
        h = 0;
        w = 0;
        body = {};
    }

    explicit Matrix(const std::vector<std::vector<int>>& data) :
        body(data), h(data.size()), w(data[0].size()) {
    }

    explicit Matrix(std::size_t n) {
        h = n;
        w = n;
        body.assign(n, {});
        for (std::size_t i = 0; i < n; ++i) {
            body[i].assign(n, 0);
            body[i][i] = 1;
        }
    }
};


#endif //FINITE_HOMOLOGIES_MATRIX_H
