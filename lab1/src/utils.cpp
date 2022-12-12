//
// Created by Aleksey Kholodov on 12.12.2022.
//

#include <vector>
#include "oneapi/tbb.h"

namespace quicksort_utils {

    int partition(std::vector<int> &arr, int start, int end) {
        int pivot = arr[start];

        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (arr[i] <= pivot)
                count++;
        }

        int pivotIndex = start + count;
        std::swap(arr[pivotIndex], arr[start]);

        int i = start, j = end;
        while (i < pivotIndex && j > pivotIndex) {
            while (arr[i] <= pivot) {
                i++;
            }
            while (arr[j] > pivot) {
                j--;
            }
            if (i < pivotIndex && j > pivotIndex) {
                std::swap(arr[i++], arr[j--]);
            }
        }
        return pivotIndex;
    }

    void seqQuickSort(std::vector<int> &arr, int start, int end) {
        if (start >= end)
            return;
        int p = partition(arr, start, end);
        seqQuickSort(arr, start, p - 1);
        seqQuickSort(arr, p + 1, end);
    }

    void parQuickSort(tbb::task_arena arena, std::vector<int> &arr, int start, int end) {
        if (start >= end)
            return;
        int p = partition(arr, start, end);

        tbb::task_group g;

        arena.execute([&arr, &start, &p, &end] {
            tbb::parallel_invoke([&] { seqQuickSort(arr, start, p - 1); },
                                 [&] { seqQuickSort(arr, p + 1, end); });
        });
    }

    void parQuickSort(std::vector<int> &arr, int start, int end) {
        tbb::task_arena arena(4);
        parQuickSort(arena, arr, start, end);
    }
}