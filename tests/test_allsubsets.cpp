//
// Created by Artem Malko on 05.05.2024.
//

#include "test_allsubsets.h"

void PrintAns(std::vector<std::set<std::vector<bool>>>& ans) {
    std::cout << "[";
    for (auto& ss : ans) {
        std::cout << "{";
        for (auto& elem : ss) {
            std::cout << "(";
            for (bool fl : elem) {
                std::cout << fl << ", ";
            }
            std::cout << "), ";
        }
        std::cout << "}, ";
    }
    std::cout << "]";
}

bool CheckVectors(const std::vector<bool>& res,
                  const std::vector<bool>& ans) {
    if (res.size() != ans.size()) {
        return false;
    }

    for (int i = 0; i < res.size(); ++i) {
        if (res[i] != ans[i]) {
            return false;
        }
    }

    return true;
}

bool CheckSets(std::set<std::vector<bool>>& res,
               std::set<std::vector<bool>>& ans) {
    if (res.size() != ans.size()) {
        return false;
    }
    auto it_a = res.begin();
    auto it_b = ans.begin();
    for (int i = 0; i < res.size(); ++i) {
        if (!CheckVectors(*it_a, *it_b)) {
            return false;
        }
        ++it_a;
        ++it_b;
    }

    return true;
}

bool CheckResult(std::vector<std::set<std::vector<bool>>>& res,
                 std::vector<std::set<std::vector<bool>>>& ans) {
    TOTAL_TESTS_SUBSET++;
    if (res.size() != ans.size()) {
        return false;
    }

    for (int i = 0; i < res.size(); ++i) {
        if (!CheckSets(res[i], ans[i])) {
            std::cout << "--------------------------------\n";
            std::cout << "Test Case Failed" << "\n\n";
            std::cout << "Solve function returned: \n";
            PrintAns(res);
            std::cout << "\nReal answer: \n";
            PrintAns(ans);
            std::cout << "\n--------------------------------\n\n";
            return false;
        }
    }

    PASSED_TESTS_SUBSET++;
    return true;
}

void RunAllSubsetsTests() {
    // Simple case, one mask
    {
        std::vector<std::vector<bool>> masks = {
                {true, true, true}
        };
        auto res = GetAllSubsets(masks);
        std::vector<std::set<std::vector<bool>>> ans(4);
        ans[3].insert({true, true, true});

        ans[2].insert({false, true, true});
        ans[2].insert({true, false, true});
        ans[2].insert({true, true, false});

        ans[1].insert({false, false, true});
        ans[1].insert({true, false, false});
        ans[1].insert({false, true, false});

        ans[0].insert({false, false, false});

        CheckResult(res, ans);
    }

    // Two masks
    {
        std::vector<std::vector<bool>> masks = {
                {true, false, true},
                {false, true, false}
        };
        auto res = GetAllSubsets(masks);
        std::vector<std::set<std::vector<bool>>> ans(3);
        ans[2].insert({true, false, true});

        ans[1].insert({false, false, true});
        ans[1].insert({true, false, false});
        ans[1].insert({false, true, false});

        ans[0].insert({false, false, false});

        CheckResult(res, ans);
    }

    std::cout << "Passed " << PASSED_TESTS_SUBSET << "/" << TOTAL_TESTS_SUBSET << "\n\n";
    if (TOTAL_TESTS_SUBSET == PASSED_TESTS_SUBSET) {
        std::cout << "All tests passed" << "\n";
    } else {
        std::cout << "Failed on " << TOTAL_TESTS_SUBSET - PASSED_TESTS_SUBSET << " tests\n";
    }
}
