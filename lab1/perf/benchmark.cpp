//
// Created by Aleksey Kholodov on 05.12.2022.
//

#include <random>
#include <vector>
#include "../src/utils.h"
#include "benchmark/benchmark.h"

static void bench_quicksort(benchmark::State& state, std::function<void(std::vector<int>)> fun) {
    for (auto _ : state) {
        state.PauseTiming();
        std::mt19937 gen(1337);
        int n = 1e8;
        std::vector<int> vec(n);
        for (int i = 0; i < n; i++) {
            vec[i] = gen();
        }
        state.ResumeTiming();
        fun(vec);
    }
}

static void bench_seq(benchmark::State& state) {
    bench_quicksort(state, [](std::vector<int> vec) {
        quicksort_utils::seqQuickSort(vec, 0, vec.size() - 1);
    });
}

static void bench_par(benchmark::State& state) {
    bench_quicksort(state, [](std::vector<int> vec) {
        quicksort_utils::parQuickSort(vec, 0, vec.size() - 1);
    });
}

BENCHMARK(bench_seq) -> Iterations(4) -> UseRealTime();
BENCHMARK(bench_par) -> Iterations(4) -> UseRealTime();

BENCHMARK_MAIN();