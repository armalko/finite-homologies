//
// Created by Artem Malko on 28.02.2024.
//

#include "test_maxchains.h"

void PrintAns(std::vector<std::list<std::size_t>>& l) {
    for (auto& path : l) {
        for (auto u = path.begin(); u != path.end(); ++u) {
            std::cout << *u + 1;
            if (u != --path.end()) {
                std::cout << "-";
            }
        }
        std::cout << "\n";
    }
}

bool CheckLists(std::list<std::size_t>& a, std::list<std::size_t>& b) {
    if (a.size() != b.size()) {
        return false;
    }
    auto it_a = a.begin();
    auto it_b = b.begin();
    for (int i = 0; i < a.size(); ++i) {
        if (*it_a != *it_b) {
            return false;
        }
        ++it_a;
        ++it_b;
    }

    return true;
}


bool TestCase(PoSet graph, std::vector<std::list<std::size_t>> ans) {
    ++TOTAL_TESTS;

    auto sol = FindMaxChains(graph);
    std::sort(sol.begin(), sol.end());
    std::sort(ans.begin(), ans.end());

    if (sol.size() != ans.size()) {
        std::cout << "--------------------------------\n";
        std::cout << "Test Case Failed" << "\n\n";
        std::cout << "Solve function returned: \n";
        PrintAns(sol);
        std::cout << "\nReal answer: \n";
        PrintAns(ans);
        std::cout << "--------------------------------\n\n";
        return false;
    }

    for (std::size_t i = 0; i < ans.size(); ++i) {
        if (!CheckLists(sol[i], ans[i])) {
            std::cout << "--------------------------------\n";
            std::cout << "Test Case Failed" << "\n\n";
            std::cout << "Solve function returned: \n";
            PrintAns(sol);
            std::cout << "\nReal answer: \n";
            PrintAns(ans);
            std::cout << "--------------------------------\n\n";
            return false;
        }
    }

    ++PASSED_TESTS;
    std::cout << "Test Case Passed" << "\n";

    return true;
}

void RunMaxChainTests() {
    // Simple Cases
    {
        PoSet p({{0, 1},
                 {1, 2},
                 {2, 3}});
        TestCase(p, {{0, 1, 2, 3}});

        PoSet p1({{0, 1},
                  {1, 3},
                  {2, 3},
                  {0, 2}});
        TestCase(p1, {{0, 1, 3}, {0, 2, 3}});

        PoSet p2({{3, 0},
                  {4, 0},
                  {0, 1},
                  {0, 2}});
        TestCase(p2, {{3, 0, 1}, {3, 0, 2}, {4, 0, 1}, {4, 0, 2}});

        PoSet p3({{3, 0},
                  {4, 0},
                  {0, 1},
                  {0, 2},
                  {1, 5},
                  {2, 5}});
        TestCase(p3, {{3, 0, 1, 5}, {3, 0, 2, 5}, {4, 0, 1, 5}, {4, 0, 2, 5}});
    }

    // More than one connectivity components
    {
        PoSet p({{0, 1},
                 {1, 2},
                 {2, 3},
                 {4, 5}});
        TestCase(p, {{0, 1, 2, 3}, {4, 5}});

        PoSet p1({{0, 1},
                 {1, 2},
                 {2, 3},
                 {4, 5}});
        TestCase(p1, {{0, 1, 2, 3}, {4, 5}});
    }


    std::cout << "Passed " << PASSED_TESTS << "/" << TOTAL_TESTS << "\n\n";
    if (TOTAL_TESTS == PASSED_TESTS) {
        std::cout << "All tests passed" << "\n";
    } else {
        std::cout << "Failed on " << TOTAL_TESTS - PASSED_TESTS << " tests\n";
    }
}

