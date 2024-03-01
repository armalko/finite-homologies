//
// Created by Artem Malko on 18.02.2024.
//

#ifndef FINITE_HOMOLOGIES_POSET_H
#define FINITE_HOMOLOGIES_POSET_H

#include <stdexcept>
#include <list>
#include "unordered_set"
#include <map>
#include "vertex.h"
#include "edge.h"

class [[maybe_unused]] SComplex;

class PoSet {
public:
    std::vector<Vertex> vertices;
    std::vector<std::vector<Edge>> edges;
    std::size_t size_;

    explicit PoSet(std::vector<std::pair<int, int>>& edges_,
          const std::vector<Matrix>& operators_ = {}) {
        int max_index = 0;

        for (auto& p : edges_) {
            max_index = std::max(max_index, p.first);
            max_index = std::max(max_index, p.second);
        }
        size_ = max_index + 1;

        vertices.resize(max_index + 1);
        edges.resize(max_index + 1);

        for (std::size_t i = 0; i < edges_.size(); ++i) {
            auto p = edges_[i];
            vertices[p.first].SetIndex(p.first);
            vertices[p.second].SetIndex(p.second);

            edges[p.first].emplace_back(vertices[p.first], vertices[p.second]);

            if (!operators_.empty()) {
                edges[p.first].back().SetMat(operators_[i]);
            }
        }
    }

    explicit PoSet(std::vector<std::pair<int, int>>&& edges_,
                   std::vector<Matrix>&& operators_ = {}) : PoSet(edges_, operators_) {
    }

    PoSet(std::vector<std::pair<int, int>>& edges_,
          std::vector<int>& dimensions,
          std::vector<Matrix>& operators_) : PoSet(edges_, operators_) {
        if (operators_.size() != edges_.size()) {
            throw std::invalid_argument("Amount of edges doesn't equal to amount of operators");
        }

        for (std::size_t i = 0; i < dimensions.size(); ++i) {
            vertices[i].SetDimension(dimensions[i]);
        }
    }

    explicit PoSet(SComplex& sc);

    [[nodiscard]] std::size_t size() const {
        return size_;
    }

    bool IsCommutative();
};

template<class Iterable>
std::optional<std::pair<std::vector<int>, std::vector<int>>> GetDifference(Iterable& ch1, Iterable& ch2);

std::map<std::pair<int, int>, std::vector<std::vector<int>>> FindPaths (PoSet& poset);

void dfs(PoSet& poset,
         std::vector<std::vector<Edge>>& anti_graph,
         std::vector<std::vector<std::list<std::size_t>>>& max_paths,
         std::vector<bool>& was,
         std::size_t current);

void FindBiggest(PoSet& poset,
                 std::vector<std::vector<Edge>>& anti_graph,
                 std::unordered_set<std::size_t>& result,
                 std::vector<bool>& was,
                 std::size_t current);

std::vector<std::vector<Edge>> BuildAntiGraph(PoSet& graph);

std::vector<std::list<std::size_t>> FindMaxChains(PoSet& graph);

#endif //FINITE_HOMOLOGIES_POSET_H
