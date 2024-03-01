//
// Created by Artem Malko on 28.02.2024.
//

#ifndef FINITE_HOMOLOGIES_TEST_POSET_H
#define FINITE_HOMOLOGIES_TEST_POSET_H

#include "../poset.h"
#include "../scomplex.h"

inline int TOTAL_TESTS_POSET = 0;
inline int PASSED_TESTS_POSET = 0;

bool TestCase(PoSet p, SComplex complex);

void RunPoSetFromComplexTests();

#endif //FINITE_HOMOLOGIES_TEST_POSET_H
