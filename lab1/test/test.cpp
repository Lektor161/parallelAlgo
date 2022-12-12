//
// Created by Aleksey Kholodov on 12.12.2022.
//

#include <algorithm>

#include <gtest/gtest.h>
#include <random>

#include "../src/utils.h"

void test_qsort(std::vector<int> vec, const std::function<void(std::vector<int>&)>& fun) {
    auto vec2 = vec;
    std::sort(vec.begin(), vec.end());
    fun(vec2);
    EXPECT_EQ(vec, vec2);
}

void test_qsort(const std::vector<int>& vec) {
    test_qsort(vec, [](std::vector<int>& v){quicksort_utils::seqQuickSort(v, 0, v.size() - 1);});
    test_qsort(vec, [](std::vector<int>& v){quicksort_utils::parQuickSort(v, 0, v.size() - 1);});
}

TEST(UNIT, EMPTY) {
    test_qsort({});
}

TEST(UNIT, ONE) {
    test_qsort({2});
}

TEST(Unit, DifferentValues) {
    test_qsort({4, 1, 45, 54, 32, 23, 54, 34});
}

TEST(Unit, RepeatingValues) {
    test_qsort({1, 2, 4, 5, 6, 4});
}

TEST(Stress, Big) {
    const size_t AMOUNT = 1000;
    const size_t SIZE = 1000;

    std::mt19937 gen;

    for (size_t i = 0; i < AMOUNT; ++i) {
        std::vector<int> vec(SIZE);
        for (size_t j = 0; j < SIZE; ++j) {
            vec[j] = gen() % 5;
        }
        test_qsort(vec);
    }
}