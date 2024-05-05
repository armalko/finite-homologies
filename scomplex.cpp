//
// Created by Artem Malko on 23.02.2024.
//

#include "scomplex.h"

std::vector<std::set<std::vector<bool>>> GetAllSubsets(const std::vector<std::vector<bool>>& bit_masks) {
    std::size_t max_ones = 0;
    for (auto& mask : bit_masks) {
        max_ones = std::max(max_ones,
                            static_cast<std::size_t>(std::count(mask.begin(), mask.end(), 1)));
    }

    std::vector<std::set<std::vector<bool>>> res (max_ones);

    for (auto& mask : bit_masks) {
        std::vector<std::size_t> ones_indexes;
        std::size_t ones_amount = 0;
        for (std::size_t i = 0; i < mask.size(); ++i) {
            if (mask[i]) {
                ones_indexes.push_back(i);
                ones_amount++;
            }
        }

        for (std::int64_t i = 0; i < std::pow(2ll, ones_amount); ++i) {
            std::vector<bool> current = mask;
            std::size_t rem_ones = 0;
            for (std::size_t j = 0; j < ones_amount; ++j) {
                if (i & (1ll << j)) {
                    current[ones_indexes[j]] = false;
                    rem_ones++;
                }
            }
            if (ones_amount == rem_ones) {
                continue;
            }

            res[ones_amount - rem_ones - 1].insert(current);
        }
    }

    return res;
}

