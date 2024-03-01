//
// Created by Artem Malko on 28.02.2024.
//

#include "test_poset.h"
#include "iostream"

void PrintAns(std::vector<std::vector<Vertex>>& l) {
    for (auto& path : l) {
        for (auto u = path.begin(); u != path.end(); ++u) {
            std::cout << u->index + 1;
            if (u != --path.end()) {
                std::cout << "-";
            }
        }
        std::cout << "\n";
    }
}

bool CheckVectors(std::vector<Vertex>& a, std::vector<Vertex>& b) {
    if (a.size() != b.size()) {
        return false;
    }
    auto it_a = a.begin();
    auto it_b = b.begin();
    for (int i = 0; i < a.size(); ++i) {
        if (it_a->index != it_b->index) {
            return false;
        }
        ++it_a;
        ++it_b;
    }

    return true;
}

bool TestCase(PoSet p, SComplex complex) {
    ++TOTAL_TESTS_POSET;
    SComplex ans(p);
    auto comp =
            [](const std::vector<Vertex>& x, const std::vector<Vertex>& y){
                for (std::size_t i = 0; i < std::min(x.size(), y.size()); ++i) {
                    if (x.at(i).index < y.at(i).index) {
                        return true;
                    } else if (x.at(i).index > y.at(i).index) {
                        return false;
                    }
                }
                return true;
    };

    std::sort(ans.max_subsets.begin(), ans.max_subsets.end(), comp);
    std::sort(complex.max_subsets.begin(), complex.max_subsets.end(), comp);

    if (ans.max_subsets.size() != complex.max_subsets.size()) {
        std::cout << "--------------------------------\n";
        std::cout << "Test Case Failed" << "\n\n";
        std::cout << "Solve function returned: \n";
        PrintAns(ans.max_subsets);
        std::cout << "\nReal answer: \n";
        PrintAns(complex.max_subsets);
        std::cout << "--------------------------------\n\n";
        return false;
    }

    for (std::size_t i = 0; i < complex.max_subsets.size(); ++i) {
        if (!CheckVectors(ans.max_subsets[i], complex.max_subsets[i])) {
            std::cout << "--------------------------------\n";
            std::cout << "Test Case Failed" << "\n\n";
            std::cout << "Solve function returned: \n";
            PrintAns(ans.max_subsets);
            std::cout << "\nReal answer: \n";
            PrintAns(complex.max_subsets);
            std::cout << "--------------------------------\n\n";
            return false;
        }
    }

    ++PASSED_TESTS_POSET;
    std::cout << "Test Case Passed" << "\n";

    return true;


}

void RunPoSetFromComplexTests() {
    // Simple Cases
    {
        PoSet p({{0, 1},
                 {1, 2},
                 {2, 3}});
        SComplex s({{0, 1, 2, 3}});
        TestCase(p, s);
    }

}