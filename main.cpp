#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <time.h>
#include "header.h"

int main() {
    int n = 5;
    int block_size = 3;

    std::vector <std::vector <int>> matrix1 = matrixGenerator(6, n);
    std::vector <std::vector <int>> matrix2 = matrixGenerator(n, 7);

    double timeSpent = 0.0;
    clock_t begin = clock();

    matricesMultiplication(matrix1, matrix2);

    clock_t end = clock();
    timeSpent += (double)(end - begin) ;

    std::cout << timeSpent / CLOCKS_PER_SEC << " in seconds" << std::endl;
    std::cout << timeSpent << " in ticks" << std::endl;

    double timeSpent2 = 0.0;
    clock_t begin2 = clock();

//    Multithreading
    std::vector <std::vector<int>> c = multiply_matrix(matrix1, matrix2, block_size);

//    printMatrix(c);

    clock_t end2 = clock();
    timeSpent2 += (double)(end2 - begin2) ;

    std::cout << timeSpent2 / CLOCKS_PER_SEC << " in seconds" << std::endl;
    std::cout << timeSpent2 << " in ticks" << std::endl;

    return 0;
}

void matricesMultiplication(const std::vector <std::vector <int>> matrix1, const std::vector <std::vector <int>> matrix2) {
    std::vector <std::vector <int>> result = {};

//  Check for matrices dimensions
    for (int i = 1; i < matrix1.size(); i++) {
        if (matrix1[0].size() != matrix1[i].size()) {
            std::cout << "Error: matrix1 has different rows" << std::endl;
            return;
        }
    }

    for (int i = 1; i < matrix2.size(); i++) {
        if (matrix2[0].size() != matrix2[i].size()) {
            std::cout << "Error: matrix2 has different rows" << std::endl;
            return;
        }
    }

    if (matrix1[0].size() != matrix2.size()) {
        std::cout << "Error: matrices have wrong dimensions" << std::endl;
        return;
    }


    for (int i = 0; i < matrix1.size(); i++) {
        result.push_back({});
        for (int j = 0; j < matrix2[0].size(); j++) {

            int c = 0;
            for (int k = 0; k < matrix1[0].size(); k++) {
                c += matrix1[i][k] * matrix2[k][j];
            }
            result[i].push_back(c);
        }
    }

    printMatrix(result);
};

void printMatrix(const std::vector <std::vector <int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector <std::vector <int>> matrixGenerator(const int n, const int m) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1,6);

    std::vector <std::vector <int>> result = {};

    for (int i = 0; i < n; i++) {
        result.push_back({});
        for (int j = 0; j < m; j++) {
            result[i].push_back(dist(gen));
        }
    }

    return result;
}

// Blocks multiplication
void multiply_block(const std::vector <std::vector <int>>& a, const std::vector <std::vector <int>>& b, std::vector <std::vector <int>>& c, int block_size, int i, int j) {
    for (int k = 0; k < block_size; ++k) {
        for (int l = 0; l < block_size; ++l) {
            for (int m = 0; m < block_size; ++m) {
                c[i+k][j+l] += a[i+k][m] * b[m][j+l];
            }
        }
    }
}

// Multithreading
std::vector <std::vector <int>> multiply_matrix(const std::vector <std::vector <int>>& a, const std::vector <std::vector <int>>& b, int block_size) {
    int n = a.size();
    int m = b[0].size();
    std::vector <std::vector<int>> c(n, std::vector<int>(m));

    std::vector <std::thread> threads;
    for (int i = 0; i < n; i += block_size) {
        for (int j = 0; j < m; j += block_size) {
            threads.emplace_back(multiply_block, ref(a), ref(b), ref(c), block_size, i, j);
        }
    }

    for (auto& t : threads) {
        t.join();
    }

//    std::thread th1(multiply_block, ref(a), ref(b), ref(c), block_size, 0, 0);
//    std::thread th2(multiply_block, ref(a), ref(b), ref(c), block_size, 5, 5);
//    th1.join();
//    th2.join();

    return c;
}
