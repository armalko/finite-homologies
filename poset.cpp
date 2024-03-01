//
// Created by Artem Malko on 18.02.2024.
//

#include "poset.h"
#include "scomplex.h"
#include <map>

PoSet::PoSet(SComplex& sc) {
    std::size_t max_v = 0;
    for (auto& set : sc.max_subsets) {
        for (Vertex& v : set) {
            max_v = std::max(max_v, v.index);
        }
    }

    vertices.resize(max_v + 1);
    edges.resize(max_v + 1);
    size_ = max_v + 1;

    for (auto& set : sc.max_subsets) {
        for (Vertex& v : set) {
            vertices[v.index] = v;
        }
    }

    for (auto& set : sc.max_subsets) {
        for (std::size_t i = 1; i < set.size(); ++i) {
            edges[set[i - 1].index].emplace_back(set[i - 1], set[i]);
        }
    }
}

bool PoSet::IsCommutative() {
    auto paths = FindPaths(*this);

    // Now we have all paths that need to be checked between vertices
    // TBD

    return true;
}

template<class Iterable>
std::optional<std::pair<std::vector<int>, std::vector<int>>> GetDifference(Iterable& ch1, Iterable& ch2) {
    // Takes two vectors (lists) and return their difference.
    // Example:
    //
    // ch1 = {1, 3, 4, 7, 8, 10, 11}
    // ch2 = {1, 3, 5, 6, 9, 10, 11}
    //
    // Will return {{3, 4, 7, 8, 10},
    //              {3, 5, 6, 9, 10}}
    //
    // Note: Will return only first difference

    if (ch1.empty() || ch2.empty()) {
        return {};
    }

    if (*ch1.begin() != *ch2.begin()) {
        return {};
    }

    std::pair<std::vector<int>, std::vector<int>> result;

    auto it_a = ++ch1.begin();
    auto it_b = ++ch2.begin();
    auto prev_a = ch1.begin();
    auto prev_b = ch2.begin();

    bool same = true;
    for (int i = 1; i < std::min(ch1.size(), ch2.size()); ++i) {
        if (*it_a != *it_b) {
            if (same) {
                result.first.push_back(*prev_a);
                result.second.push_back(*prev_b);
                same = false;
            }
            result.first.push_back(*it_a);
            result.second.push_back(*it_b);
        } else {
            result.first.push_back(*it_a);
            result.second.push_back(*it_b);
            break;
        }
        ++it_a;
        ++it_b;
        ++prev_a;
        ++prev_b;
    }

    return result;
}

std::map<std::pair<int, int>, std::vector<std::vector<int>>> FindPaths (PoSet& poset) {
    auto chains = FindMaxChains(poset);

    auto max_index = [](const std::vector<std::list<std::size_t>>& data) -> std::size_t {
        std::size_t cur_max = 0;
        for (auto& chain : data) {
            cur_max = std::max(chain.size(), cur_max);
        }
        return cur_max;
    };

    // Currently works for O(n^2 * m), where n is chains amount and m - it's length
    // Will be reworked in future updates

    std::map<std::pair<int, int>, std::vector<std::vector<int>>> result;

    for (std::size_t i = 0; i < chains.size(); ++i) {
        for (std::size_t j = 0; j < i; ++j) {
            auto diff = GetDifference(chains[i], chains[j]);
            if (diff.has_value()) {
                result[{i, j}].push_back(diff.value().first);
                result[{i, j}].push_back(diff.value().second);
            }
        }
    }

    return result;
}


void dfs(PoSet& poset,
         std::vector<std::vector<Edge>>& anti_graph,
         std::vector<std::vector<std::list<std::size_t>>>& max_paths,
         std::vector<bool>& was,
         std::size_t current) {
    was[current] = true;
    if (poset.edges[current].empty()) {
        max_paths[current].push_back({current});
    }

    for (Edge& v : poset.edges[current]) {
        std::size_t cur_index = v.to->index;
        if (max_paths[cur_index].empty()) {
            dfs(poset, anti_graph, max_paths, was, cur_index);
        }
        for (auto& path : max_paths[cur_index]) {
            max_paths[current].push_back(path);
            max_paths[current].back().push_front(current);
        }
    }

    for (Edge& v : anti_graph[current]) {
        std::size_t cur_index = v.to->index;
        if (!was[cur_index] && max_paths[cur_index].empty()) {
            dfs(poset, anti_graph, max_paths, was, cur_index);
        }
    }
}

void FindBiggest(PoSet& poset,
                 std::vector<std::vector<Edge>>& anti_graph,
                 std::unordered_set<std::size_t>& result,
                 std::vector<bool>& was,
                 std::size_t current) {
    was[current] = true;
    if (anti_graph[current].empty()) {
        result.insert(current);
    }

    for (Edge& v : anti_graph[current]) {
        std::size_t cur_index = v.to->index;
        if (!was[cur_index]) {
            FindBiggest(poset, anti_graph, result, was, cur_index);
        }
    }

    for (Edge& v : poset.edges[current]) {
        std::size_t cur_index = v.to->index;
        if (!was[cur_index]) {
            FindBiggest(poset, anti_graph, result, was, cur_index);
        }
    }
}

std::vector<std::vector<Edge>> BuildAntiGraph(PoSet& graph) {
    std::size_t n = graph.size();
    std::vector<std::vector<Edge>> anti_graph(n);

    for (int i = 0; i < n; ++i) {
        for (Edge& v : graph.edges[i]) {
            anti_graph[v.to->index].emplace_back(v.to, v.from, v.GetMat());
        }
    }

    return anti_graph;
}

std::vector<std::list<std::size_t>> FindMaxChains(PoSet& graph) {
    std::size_t n = graph.size();
    auto anti_graph = BuildAntiGraph(graph);

    std::vector<std::vector<std::list<std::size_t>>> max_paths(n);
    std::unordered_set<std::size_t> biggest;
    std::vector<bool> was(n);
    was.assign(n, false);
    std::size_t current = 0;
    while (current < n) {
        dfs(graph, anti_graph, max_paths, was, current);
        while (current < n && was[current]) {
            ++current;
        }
    }
    was.assign(n, false);

    current = 0;
    while (current < n) {
        FindBiggest(graph, anti_graph, biggest, was, current);
        while (current < n && was[current]) {
            ++current;
        }
    }

    std::vector<std::list<std::size_t>> res;
    for (std::size_t v : biggest) {
        for (auto& path : max_paths[v]) {
            res.push_back(path);
        }
    }

    return res;
}
