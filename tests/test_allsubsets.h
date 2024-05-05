//
// Created by Artem Malko on 05.05.2024.
//

#ifndef FINITE_HOMOLOGIES_TEST_ALLSUBSETS_H
#define FINITE_HOMOLOGIES_TEST_ALLSUBSETS_H

#pragma once

#include "../scomplex.h"

inline int TOTAL_TESTS_SUBSET = 0;
inline int PASSED_TESTS_SUBSET = 0;

bool CheckVectors(const std::vector<bool>& res,
                  const std::vector<bool>& ans);

bool CheckSets(std::set<std::vector<bool>>& res,
               std::set<std::vector<bool>>& ans);

bool CheckResult(std::vector<std::set<std::vector<bool>>>& res,
                 std::vector<std::set<std::vector<bool>>>& ans);

void RunAllSubsetsTests();

#endif //FINITE_HOMOLOGIES_TEST_ALLSUBSETS_H
