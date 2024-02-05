#include <benchmark/benchmark.h>
#include <vector>
#include <cmath>

using namespace std;

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void FindPrimes(benchmark::State& state) {
    state.SetLabel("No OpenMP");

    int N = state.range(0);
    for (auto _ : state) {
        std::vector<int> primes;
        for (int i = 2; i <= N; ++i) {
            if (is_prime(i)) {
                primes.push_back(i);
            }
        }
        benchmark::DoNotOptimize(primes);
    }
}

void FindPrimes_OpenMP(benchmark::State& state) {
    state.SetLabel("With OpenMP");

    int N = state.range(0);
    for (auto _ : state) {
        std::vector<int> primes;

        #pragma omp parallel for schedule(dynamic)
        for (int i = 2; i <= N; ++i) {
            if (is_prime(i)) {
                #pragma omp critical
                primes.push_back(i);
            }
        }

        benchmark::DoNotOptimize(primes);
    }
}

unsigned long long MAX_N = pow(10, 7);
BENCHMARK(FindPrimes)->RangeMultiplier(10)->Range(2, MAX_N)->Unit(benchmark::kMicrosecond);
BENCHMARK(FindPrimes_OpenMP)->RangeMultiplier(10)->Range(2, MAX_N)->Unit(benchmark::kMicrosecond);


BENCHMARK_MAIN();
