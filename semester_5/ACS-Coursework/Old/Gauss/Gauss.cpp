#include <iostream>
#include <vector>
#include <benchmark/benchmark.h>
#include <random>

using namespace std;


vector<vector<double>> generateRandomExtendedMatrix(int n) {
    srand(0);

    vector<vector<double>> matrix(n, vector<double>(n + 1, 0.0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            matrix[i][j] = rand();
        }
    }

    return matrix;
}

static void BM_GaussianSolution(benchmark::State& state) {
    state.SetLabel("No OpenMP");

    int size = state.range(0);
    auto matrix = generateRandomExtendedMatrix(size);

    for (auto _ : state) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        // Приведение матрицы к верхнетреугольному виду
        for (int i = 0; i < rows - 1; i++) {
            for (int k = i + 1; k < rows; k++) {
                double factor = matrix[k][i] / matrix[i][i];
                for (int j = i; j < cols; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }

        // Обратный ход 
        vector<double> solution(rows, 0.0);

        for (int i = rows - 1; i >= 0; i--) {
            solution[i] = matrix[i][cols - 1] / matrix[i][i];
            for (int k = i - 1; k >= 0; k--) {
                matrix[k][cols - 1] -= matrix[k][i] * solution[i];
            }
        }
    }
}

static void BM_GaussianSolution_OpenMP(benchmark::State& state) {
    state.SetLabel("With OpenMP");

    int size = state.range(0);
    auto matrix = generateRandomExtendedMatrix(size);

    for (auto _ : state) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        // Приведение матрицы к верхнетреугольному виду
        #pragma omp parallel for schedule(dynamic) 
        for (int i = 0; i < rows - 1; i++) {
            for (int k = i + 1; k < rows; k++) {
                double factor = matrix[k][i] / matrix[i][i];
                for (int j = i; j < cols; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }

        // Обратный ход 
        vector<double> solution(rows, 0.0);
        #pragma omp parallel for schedule(dynamic) 
        for (int i = rows - 1; i >= 0; i--) {
            solution[i] = matrix[i][cols - 1] / matrix[i][i];

            for (int k = i - 1; k >= 0; k--) {
                matrix[k][cols - 1] -= matrix[k][i] * solution[i];
            }
        }
    }
}


void generateRange(benchmark::internal::Benchmark* b) {
    for (int i = 100; i <= 6'00; i += 100)
        b->Arg(i);
}

BENCHMARK(BM_GaussianSolution)->Apply(generateRange)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_GaussianSolution_OpenMP)->Apply(generateRange)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
