//
// Created by Artem Malko on 05.05.2024.
//

#ifndef FINITE_HOMOLOGIES_TEST_CHAINCOMPLEX_H
#define FINITE_HOMOLOGIES_TEST_CHAINCOMPLEX_H

#include "../chaincomplex.h"
#include <list>

void PrintAns(std::vector<std::vector<int>>& ans);

bool CheckMatrices(Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>& mat,
                   std::vector<std::vector<int>>& ans);

inline int TOTAL_TESTS_CHAIN = 0;
inline int PASSED_TESTS_CHAIN = 0;

void RunChainComplexTests();

#endif //FINITE_HOMOLOGIES_TEST_CHAINCOMPLEX_H
