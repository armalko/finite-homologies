//
// Created by Artem Malko on 23.02.2024.
//

#ifndef FINITE_HOMOLOGIES_SCOMPLEX_H
#define FINITE_HOMOLOGIES_SCOMPLEX_H

#include <vector>
#include "poset.h"
#include "vertex.h"
#include "iostream"
#include "set"

class SComplex {
public:
    std::vector<std::vector<Vertex>> max_subsets;
    std::vector<std::vector<bool>> bit_masks;

    explicit SComplex(PoSet& poset) {
        auto chains = FindMaxChains(poset);
        max_subsets.resize(chains.size());
        bit_masks.assign(chains.size(), std::vector<bool>(poset.size(), false));

        for (std::size_t ch = 0; ch < chains.size(); ++ch) {
            for (std::size_t ind : chains[ch]) {
                max_subsets[ch].push_back(poset.vertices[ind]);
                bit_masks[ch][ind] = true;
            }
        }
    }

    explicit SComplex(PoSet&& poset) {
        auto chains = FindMaxChains(poset);
        max_subsets.resize(chains.size());
        bit_masks.assign(chains.size(), std::vector<bool>(poset.size(), false));

        for (std::size_t ch = 0; ch < chains.size(); ++ch) {
            for (std::size_t ind : chains[ch]) {
                max_subsets[ch].push_back(poset.vertices[ind]);
                bit_masks[ch][ind] = true;
            }
        }
    }

    explicit SComplex(std::vector<std::vector<std::size_t>> chains) {
        max_subsets.resize(chains.size());
        std::size_t vert_amount = 0;
        for (auto& ch: chains) {
            for (std::size_t cur : ch) {
                vert_amount = std::max(vert_amount, cur);
            }
        }

        bit_masks.assign(chains.size(), std::vector<bool>(vert_amount + 1, false));

        for (std::size_t i = 0; i < chains.size(); ++i) {
            for (std::size_t j = 0; j < chains[i].size(); ++j) {
                max_subsets[i].emplace_back(chains[i][j]);
                bit_masks[i][chains[i][j]] = true;
            }
        }

    }

    SComplex(const SComplex& other) : max_subsets(other.max_subsets), bit_masks(other.bit_masks) {
    }

    SComplex(SComplex&& other) : max_subsets(std::move(other.max_subsets)),
                                 bit_masks(std::move(other.bit_masks)) {
    }

};

std::vector<std::set<std::vector<bool>>> GetAllSubsets(const std::vector<std::vector<bool>>& bit_masks);


#endif //FINITE_HOMOLOGIES_SCOMPLEX_H
