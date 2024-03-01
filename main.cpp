#include <iostream>
#include "poset.h"
#include "tests/test_maxchains.h"
#include "tests/test_poset.h"


int main() {
    RunMaxChainTests();
    RunPoSetFromComplexTests();

    return 0;
}
