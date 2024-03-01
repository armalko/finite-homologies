//
// Created by Artem Malko on 18.02.2024.
//

#ifndef FINITE_HOMOLOGIES_VERTEX_H
#define FINITE_HOMOLOGIES_VERTEX_H

#pragma once

#include <vector>
#include "matrix.h"


class Vertex {
public:
    std::size_t index;
    std::size_t dim = 0;
    Matrix mat = {};

    Vertex(std::size_t index) : index(index) {
        init_ = true;
    }

    Vertex() {
        index = 0;
    }

    std::size_t GetIndex() const {
        return index;
    }

    void SetDimension(std::size_t d) {
        dim = d;
    }

    std::size_t GetDimension() const {
        return dim;
    }

    bool IsInit() const {
        return init_;
    }

    void SetIndex(std::size_t i) {
        index = i;
        init_ = true;
    }

private:
    bool init_ = false;
};

#endif //FINITE_HOMOLOGIES_VERTEX_H
