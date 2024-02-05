#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

#define ITERATIONS 10

vector<vector<double>> generateExtendedMatrix(int n) {

    srand(0);

    vector<vector<double>> matrix(n, vector<double>(n + 1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            matrix[i][j] = rand();
        }
    }

    return matrix;
}

vector<double> gaussianSolution(vector<vector<double>> matrix) {

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

    vector<double> solution(rows);

    for (int i = rows - 1; i >= 0; i--) {
        solution[i] = matrix[i][cols - 1] / matrix[i][i];
        for (int k = i - 1; k >= 0; k--) {
            matrix[k][cols - 1] -= matrix[k][i] * solution[i];
        }
    }

    return solution;
}

vector<double> gaussianSolution_OMP(vector<vector<double>> matrix) {

    int rows = matrix.size();
    int cols = matrix[0].size();

    // Приведение матрицы к верхнетреугольному виду

    for (int i = 0; i < rows - 1; i++) {

        #pragma omp parallel for schedule(dynamic) 
        for (int k = i + 1; k < rows; k++) {

            double factor = matrix[k][i] / matrix[i][i];
            for (int j = i; j < cols; j++) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }

    // Обратный ход 

    vector<double> solution(rows);

    for (int i = rows - 1; i >= 0; i--) {
        solution[i] = matrix[i][cols - 1] / matrix[i][i];

        #pragma omp parallel for 
        for (int k = i - 1; k >= 0; k--) {
            matrix[k][cols - 1] -= matrix[k][i] * solution[i];
        }
    }

    return solution;
}

template <typename TimeUnits>
long long Test(vector<double>(*solution)(vector<vector<double>>), int size, int iterations) {
    vector<vector<double>> matrix = generateExtendedMatrix(size);

    long long sum = 0;

    for (int i = 0; i < iterations; i++) {
        auto start_time = chrono::high_resolution_clock::now();
        solution(matrix);
        auto end_time = chrono::high_resolution_clock::now();

        sum += chrono::duration_cast<TimeUnits>(end_time - start_time).count();
    }
    
    return sum / iterations;
}

int main() {
    cout << setw(10) << "Size" << setw(15) << "Sequential" << setw(15) << "Parallel" << setw(15) << "Speedup" << endl;
    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;

    json resultArray;

    vector<int> testValues;


    for (int n = 2; n < 50; n += 1)
        testValues.push_back(n);

    for (int n = 50; n <= 1000; n += 10)
        testValues.push_back(n);

    for (int n : testValues) {
        auto duration = Test<chrono::microseconds>(gaussianSolution, n, ITERATIONS);
        auto durationOMP = Test<chrono::microseconds>(gaussianSolution_OMP, n, ITERATIONS);

        cout << setw(10) << n << setw(15) << duration << setw(15) << durationOMP
            << setw(15) << fixed << setprecision(2) << (double)duration / durationOMP << endl;

        json resultObject;
        resultObject["n"] = n;
        resultObject["duration"] = duration;
        resultObject["durationOMP"] = durationOMP;

        resultArray.push_back(resultObject);
    }

    ofstream file("results.json");
    file << setw(4) << resultArray << endl;

    return 0;
}
