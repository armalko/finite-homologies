//
// Created by Artem Malko on 28.02.2024.
//

#ifndef FINITE_HOMOLOGIES_TEST_MAXCHAINS_H
#define FINITE_HOMOLOGIES_TEST_MAXCHAINS_H

#include "../poset.h"
#include <iostream>

void PrintAns(std::vector<std::list<std::size_t>>& l);

bool CheckLists(std::list<std::size_t>& a, std::list<std::size_t>& b);

inline int TOTAL_TESTS = 0;
inline int PASSED_TESTS = 0;

bool TestCase(PoSet graph, std::vector<std::list<std::size_t>> ans);

void RunMaxChainTests();

#endif //FINITE_HOMOLOGIES_TEST_MAXCHAINS_H
