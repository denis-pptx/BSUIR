#include <iostream>
#include <vector>
#include <iomanip>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chrono;

bool useReadyMadeMatrix = false;

// Функция для вывода матрицы
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double element : row) {
            cout << setw(8) << element;
        }
        cout << endl;
    }
}

// Функция для выполнения метода Гаусса без OpenMP
int gaussianSolutionWithoutOpenMP(vector<vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    auto start = high_resolution_clock::now();

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

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Время выполнения без OpenMP: " << duration.count() << " мк" << endl;

    // Вывод решения
    if (!useReadyMadeMatrix) {
        cout << "Решение системы уравнений:" << endl;
        for (int i = 0; i < rows; ++i) {
            cout << "x" << i + 1 << " = " << solution[i] << endl;
        }
    }

    return duration.count();
}

// Функция для выполнения метода Гаусса с OpenMP
int gaussianSolutionWithOpenMP(vector<vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    auto start = high_resolution_clock::now();

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

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Время выполнения с OpenMP: " << duration.count() << " мк" << endl;

    // Вывод решения
    if (!useReadyMadeMatrix) {
        cout << "Решение системы уравнений:" << endl;
        for (int i = 0; i < rows; ++i) {
            cout << "x" << i + 1 << " = " << solution[i] << endl;
        }
    }

    return duration.count();
}

int main() {
    setlocale(LC_ALL, "Ru");

    vector<vector<double>> matrix;

    char choice;
    cout << "Хотите ввести свою матрицу? (y/n): ";
    cin >> choice;
    useReadyMadeMatrix = !(choice == 'y' || choice == 'Y');

    if (!useReadyMadeMatrix) {
        cout << "Введите количество уравнений: ";
        int n = 0; cin >> n;

        // Создание матрицы
        matrix = vector<vector<double>>(n, vector<double>(n + 1, 0.0));

        // Ввод коэффициентов и свободных членов
        cout << "Введите коэффициенты и свободные члены:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "Уравнение " << i + 1 << ": ";
            for (int j = 0; j < n + 1; ++j) {
                cin >> matrix[i][j];
            }
        }
    }
    else {
        // Использование заготовленной матрицы
        matrix = vector<vector<double>>(1000, vector<double>(1000 + 1, 0.0));
    }

    // Вывод исходной матрицы
    if (!useReadyMadeMatrix) {
        cout << "Исходная матрица:" << endl;
        printMatrix(matrix);
    }
    
    
    auto matrix1 = matrix;
    auto matrix2 = matrix;

    // Решение системы методом Гаусса без OpenMP
    double withoutOpenMP = gaussianSolutionWithoutOpenMP(matrix1);

    // Решение системы методом Гаусса с OpenMP
    double withOpenMP = gaussianSolutionWithOpenMP(matrix2);

    cout << "С OpenMP быстрее в " << withoutOpenMP / withOpenMP << " раз";
    return 0;
}
