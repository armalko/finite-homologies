//
// Created by Artem Malko on 03.05.2024.
//

#ifndef FINITE_HOMOLOGIES_CHAINCOMPLEX_H
#define FINITE_HOMOLOGIES_CHAINCOMPLEX_H

#pragma once

#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include "scomplex.h"


class ChainComplex {
public:
    explicit ChainComplex(int length) {
        len_ = length;
        dimensions_.resize(len_);
        operators_.resize(len_ + 1);
        operators_.assign(len_ + 1, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>{{0}});
    }

    ChainComplex(const SComplex& sc) {
        auto subs = GetAllSubsets(sc.bit_masks);

        std::map<std::vector<bool>, int64_t> numbered;
        for (auto& ksimplex : subs) {
            int64_t counter = 0;
            for (auto& mask : ksimplex) {
                numbered[mask] = counter++;
            }
        }


        len_ = subs.size();
        dimensions_.resize(len_);
        operators_.resize(len_ + 1);
        operators_.assign(len_ + 1, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>{{0}});

        for (std::size_t i = 0; i < subs.size(); ++i) {
            dimensions_[i] = subs[i].size();

            if (i == 0) {
                continue;
            }

            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> eigenMatrix(subs[i - 1].size(),
                                                                              subs[i].size());

            for (const auto& bm : subs[i]) {
                int64_t cur_num = numbered[bm];
                int sign = 1;
                for (int j = 0; j < bm.size(); ++j) {
                    if (bm[j]) {
                        auto bm_copy = bm;
                        bm_copy[j] = false;
                        eigenMatrix(numbered[bm_copy], cur_num) = sign;
                        sign *= -1;
                    }
                }
            }

            operators_[i] = eigenMatrix;
        }

    }

    void SetDimension(std::size_t ind, int dim) {
        if (ind >= len_) {
            throw std::runtime_error("Too big index in SetDimension");
        }

        dimensions_[ind] = dim;
    }

    void SetOperator(std::size_t ind, const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& mat) {
        if (ind >= len_ || ind == 0) {
            throw std::runtime_error("Too big or zero index in SetOperator");
        }

        operators_[ind] = mat;
    }

    void SetOperator(std::size_t ind, const std::vector<std::vector<double>>& mat) {
        if (ind >= len_ || ind == 0) {
            throw std::runtime_error("Too big index in SetOperator");
        }

        if (mat.empty() || mat[0].empty()) {
            return;
        }

        std::size_t rows = mat.size();
        std::size_t cols = mat[0].size();

        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> eigenMatrix(rows, cols);

        for (std::size_t i = 0; i < rows; ++i) {
            for (std::size_t j = 0; j < cols; ++j) {
                eigenMatrix(i, j) = static_cast<double>(mat[i][j]);
            }
        }

        operators_[ind] = eigenMatrix;
    }

    bool CheckCorrectness() {
        for (std::size_t i = 1; i < len_; ++i) {
            if (!(operators_[i] * operators_[i - 1]).isZero()) {
                return false;
            }
        }

        return true;
    }

    const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& GetOperator(std::size_t ind) {
        if (ind >= len_ + 1) {
            throw std::runtime_error("Too big index in GetOperator");
        }

        return operators_[ind];
    }

    int GetDimension(std::size_t ind) {
        if (ind >= len_) {
            throw std::runtime_error("Too big index in GetDimension");
        }

        return dimensions_[ind];
    }

    int ComputeBetti(std::size_t ind) {
        if (ind >= len_) {
            throw std::runtime_error("Too big index in FindBetti");
        }
        int ker_dim;
        int im_dim;
        if (ind == 0) {
            ker_dim = dimensions_[0];
            im_dim = operators_[ind + 1].fullPivLu().rank();
        } else if (ind + 1 == len_) {
            ker_dim = operators_[ind].fullPivLu().dimensionOfKernel();
            im_dim = 0;
        } else if (len_ == 1) {
            return dimensions_[0];
        } else {
            ker_dim = operators_[ind].fullPivLu().dimensionOfKernel();
            im_dim = operators_[ind + 1].fullPivLu().rank();
        }


        return ker_dim - im_dim;
    }

    std::vector<int> ComputeAllBettiNumbers() {
        std::vector<int> ker_dims;
        std::vector<int> im_dims;

        for (int i = 0; i < len_ + 1; ++i) {
            if (i != 0 && i != len_) {
                auto lu = operators_[i].fullPivLu();
                ker_dims.push_back(lu.dimensionOfKernel());
                im_dims.push_back(lu.rank());
            } else {
                if (i == 0) {
                    ker_dims.push_back(dimensions_[0]);
                    im_dims.push_back(-1);
                } else {
                    ker_dims.push_back(-1);
                    im_dims.push_back(0);
                }
            }
        }

        std::vector<int> ans;

        for (int i = 0; i < len_; ++i) {
            ans.push_back(ker_dims[i] - im_dims[i + 1]);
        }

        return ans;
    }
private:
    std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> operators_;
    std::vector<int> dimensions_;
    int len_;
};


#endif //FINITE_HOMOLOGIES_CHAINCOMPLEX_H
