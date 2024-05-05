//
// Created by Artem Malko on 05.05.2024.
//

#include "test_chaincomplex.h"
#include "iostream"

void PrintAns(const std::vector<std::vector<double>>& ans) {
    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < ans[0].size(); ++j) {
            std::cout << ans[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void PrintVector(const std::vector<int>& ans) {
    for (int an : ans) {
        std::cout << an << " ";
    }
    std::cout << "\n";
}

bool CheckVectors(const std::vector<int>& res, const std::vector<int>& ans) {
    ++TOTAL_TESTS_CHAIN;

    if (res.size() != ans.size()) {
        std::cout << "--------------------------------\n";
        std::cout << "Test Case Failed" << "\n\n";
        std::cout << "Length of result: \n";
        std::cout << res.size() << "\n";
        std::cout << "Real length: \n";
        std::cout << ans.size() << "\n";
        std::cout << "--------------------------------\n\n";
        return false;
    }

    for (int i = 0; i < ans.size(); ++i) {
        if (res[i] != ans[i]) {
            std::cout << "--------------------------------\n";
            std::cout << "Test Case Failed" << "\n\n";
            std::cout << "Mat values: \n";
            PrintVector(res);
            std::cout << "Real ans: \n";
            PrintVector(ans);
            std::cout << "--------------------------------\n\n";
            return false;
        }
    }
    PASSED_TESTS_CHAIN++;
    return true;
}

bool CheckMatrices(const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& mat,
                   const std::vector<std::vector<double>>& ans) {
    ++TOTAL_TESTS_CHAIN;

    if (mat.cols() != ans[0].size() || mat.rows() != ans.size()) {
        std::cout << "--------------------------------\n";
        std::cout << "Test Case Failed" << "\n\n";
        std::cout << "Dimensions of mat: \n";
        std::cout << "(" << mat.rows() << ", " << mat.cols() << ")" << "\n";
        std::cout << "Real Dimensions: \n";
        std::cout << "(" << ans.size() << ", " << ans[0].size() << ")" << "\n";
        std::cout << "--------------------------------\n\n";
        return false;
    }

    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < ans[0].size(); ++j) {
            if (mat.coeff(i, j) != ans[i][j]) {
                std::cout << "--------------------------------\n";
                std::cout << "Test Case Failed" << "\n\n";
                std::cout << "Mat values: \n";
                std::cout << mat << "\n";
                std::cout << "Real ans: \n";
                PrintAns(ans);
                std::cout << "--------------------------------\n\n";
                return false;
            }
        }
    }
    PASSED_TESTS_CHAIN++;
    return true;
}

bool CheckInts(int a, int ans) {
    ++TOTAL_TESTS_CHAIN;

    if (a != ans) {
        std::cout << "--------------------------------\n";
        std::cout << "Test Case Failed" << "\n\n";
        std::cout << "Betti number returned: \n";
        std::cout << a << "\n";
        std::cout << "Real answer: \n";
        std::cout << ans << "\n";
        std::cout << "--------------------------------\n\n";
        return false;
    }

    PASSED_TESTS_CHAIN++;
    return true;
}

void RunChainComplexTests() {
    // Basic Functionality
    {
        ChainComplex ch (3);
        ch.SetOperator(1, {{0, 1, 2},
                           {3, 4, 5},
                           {6, 7, 8}});
        CheckMatrices(ch.GetOperator(1), {{0, 1, 2},
                                          {3, 4, 5},
                                          {6, 7, 8}});

        ch.SetOperator(1, {{0, 1}});
        CheckMatrices(ch.GetOperator(1), {{0, 1}});
    }

    // Betti numbers check
    {
        ChainComplex ch (2);

        ch.SetOperator(1, {{1, -1, 0},
                           {-1, 0, 1},
                           {0, 1, -1}});

        ch.SetDimension(0, 3);
        ch.SetDimension(1, 3);

        CheckInts(ch.ComputeBetti(1), 1);
        CheckVectors(ch.ComputeAllBettiNumbers(), {1, 1});
    }

    // From SComplex
    {
        SComplex sc ({{0, 1}, {0, 2}, {1, 2}});
        ChainComplex ch (sc);
        CheckVectors(ch.ComputeAllBettiNumbers(), {1, 1});

        SComplex sc1 ({{0, 1, 2}, {0, 2, 3}, {1, 2, 3}, {0, 1, 3}});
        ChainComplex ch1 (sc1);
        CheckVectors(ch1.ComputeAllBettiNumbers(), {1, 0, 1});

        SComplex sc2 ({{0, 1, 2, 3}});
        ChainComplex ch2 (sc2);
        CheckVectors(ch2.ComputeAllBettiNumbers(), {1, 0, 0, 0});

        SComplex sc3 ({{0, 1}});
        ChainComplex ch3 (sc3);
        CheckVectors(ch3.ComputeAllBettiNumbers(), {1, 0});

        // Torus
        SComplex sc4 ({{0, 1, 5}, {0, 3, 5}, {0, 2, 3}, {0, 4, 6}, {0, 6, 2}, {0, 1, 4},
                       {1, 2, 3}, {1, 6, 5}, {1, 3, 6}, {3, 4, 6}, {5, 6, 2}, {5, 4, 2}, {5, 3, 4}, {2, 4, 1}});
        ChainComplex ch4 (sc4);
        CheckVectors(ch4.ComputeAllBettiNumbers(), {1, 2, 1});
    }

    std::cout << "Passed " << PASSED_TESTS_CHAIN << "/" << TOTAL_TESTS_CHAIN << "\n\n";
    if (TOTAL_TESTS_CHAIN == PASSED_TESTS_CHAIN) {
        std::cout << "All tests passed" << "\n";
    } else {
        std::cout << "Failed on " << TOTAL_TESTS_CHAIN - PASSED_TESTS_CHAIN << " tests\n";
    }
}