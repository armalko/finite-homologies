//
// Created by Artem Malko on 18.02.2024.
//

#ifndef FINITE_HOMOLOGIES_EDGE_H
#define FINITE_HOMOLOGIES_EDGE_H

#pragma once

#include <utility>

#include "vertex.h"
#include "matrix.h"
#include "utility"


class Edge {
public:
    std::shared_ptr<Vertex> from, to;
    Matrix mat;

    Edge(Vertex& from_, Vertex& to_) {
        from = std::make_shared<Vertex>(from_);
        to = std::make_shared<Vertex>(to_);
    }

    Edge(std::shared_ptr<Vertex> from_, std::shared_ptr<Vertex> to_) {
        from = std::move(from_);
        to = std::move(to_);
    }

    Edge(Vertex& from_, Vertex& to_, const Matrix& mat_) {
        from = std::make_shared<Vertex>(from_);
        to = std::make_shared<Vertex>(to_);
        mat = mat_;
    }

    Edge(std::shared_ptr<Vertex> from_, std::shared_ptr<Vertex> to_, const Matrix& mat_) {
        from = std::move(from_);
        to = std::move(to_);
        mat = mat_;
    }

    void SetMat(const Matrix& mat_) {
        mat = mat_;
    }

    Matrix GetMat() const {
        return mat;
    }
};

#endif //FINITE_HOMOLOGIES_EDGE_H
