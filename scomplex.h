//
// Created by Artem Malko on 23.02.2024.
//

#ifndef FINITE_HOMOLOGIES_SCOMPLEX_H
#define FINITE_HOMOLOGIES_SCOMPLEX_H

#include <vector>
#include "poset.h"
#include "vertex.h"
#include "iostream"

class SComplex {
public:
    std::vector<std::vector<Vertex>> max_subsets;

    explicit SComplex(PoSet& poset) {
        auto chains = FindMaxChains(poset);
        max_subsets.resize(chains.size());

        for (std::size_t ch = 0; ch < chains.size(); ++ch) {
            for (std::size_t ind : chains[ch]) {
                max_subsets[ch].push_back(poset.vertices[ind]);
            }
        }
    }

    explicit SComplex(PoSet&& poset) {
        auto chains = FindMaxChains(poset);
        max_subsets.resize(chains.size());

        for (std::size_t ch = 0; ch < chains.size(); ++ch) {
            for (std::size_t ind : chains[ch]) {
                max_subsets[ch].push_back(poset.vertices[ind]);
            }
        }
    }

    explicit SComplex(std::vector<std::vector<std::size_t>> chains) {
        max_subsets.resize(chains.size());

        for (std::size_t i = 0; i < chains.size(); ++i) {
            for (std::size_t j = 0; j < chains[i].size(); ++j) {
                max_subsets[i].emplace_back(chains[i][j]);
            }
        }
    }

    SComplex(const SComplex& other) : max_subsets(other.max_subsets) {
    }

    SComplex(SComplex&& other) : max_subsets(std::move(other.max_subsets)) {
    }

};


#endif //FINITE_HOMOLOGIES_SCOMPLEX_H
