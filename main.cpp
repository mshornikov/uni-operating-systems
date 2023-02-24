#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <time.h>
#include "header.h"
std::vector <std::vector <int>> emptyArray(const int n) {
    std::vector <std::vector <int>> matrix = {};

    for (int i = 0; i <= n; i++) {
        matrix.push_back({});
    }

    return matrix;
}

auto resultMatrix = emptyArray(6);
auto matrix1 = matrixGenerator(6, 5);
auto matrix2 = matrixGenerator(5, 6);

int main() {
    double timeSpent = 0.0;
    clock_t begin = clock();

    matricesMultiplication(matrix1, matrix2);

    clock_t end = clock();
    timeSpent += (double)(end - begin) ;

    std::cout << timeSpent / CLOCKS_PER_SEC << " in seconds" << std::endl;
    std::cout << timeSpent << " in ticks" << std::endl;


    double timeSpent2 = 0.0;
    clock_t begin2 = clock();

//    std::vector <std::thread> threads;
//    for (int i = 1; i < matrix1.size() + 1; i++) {
//        threads.emplace_back(multithreading, i-1, i);
//    }
//
//    for (auto& t : threads) {
//        t.join();
//    }

    std::thread th1(multithreading, 0, 3);
    std::thread th2(multithreading, 3, 6);
    th1.join();
    th2.join();
    printMatrix(resultMatrix);

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
    std::uniform_int_distribution<> dist(-1000,1000);

    std::vector <std::vector <int>> result = {};

    for (int i = 0; i < n; i++) {
        result.push_back({});
        for (int j = 0; j < m; j++) {
            result[i].push_back(dist(gen));
        }
    }

    return result;
}

void multithreading(const int start, const int end) {

    for (int i = start; i < end; i++) {
        for (int j = 0; j < matrix2[0].size(); j++) {
            int c = 0;
            for (int k = 0; k < matrix1[0].size(); k++) {
                c += matrix1[i][k] * matrix2[k][j];
            }
            resultMatrix[i].push_back(c);
        }
    }
}