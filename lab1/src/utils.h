//
// Created by Aleksey Kholodov on 12.12.2022.
//

#pragma once

#include <iostream>
#include <vector>
#include "oneapi/tbb.h"

namespace quicksort_utils {
    void seqQuickSort(std::vector<int> &arr, int start, int end);

    void parQuickSort(std::vector<int> &arr, int start, int end);
}