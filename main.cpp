#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <cmath>
#include "header.h"
std::vector <std::vector <int>> emptyArray(const int n) {
    std::vector <std::vector <int>> matrix = {};

    for (int i = 0; i <= n; i++) {
        matrix.push_back({});
    }

    return matrix;
}

const int size = 1000;
auto resultMatrix = emptyArray(size);
auto matrix1 = matrixGenerator(size, size);
auto matrix2 = matrixGenerator(size, size);

int main() {
    const double amountOfCores = 8;
    const double threadsPerCore = ceil(size / amountOfCores);
//    std::cout << threadsPerCore << std::endl;
    auto begin = std::chrono::system_clock::now();

    matricesMultiplication(matrix1, matrix2);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = (end - begin);
    std::cout << "Single threading time: " << elapsed.count() << " s\n";

    begin = std::chrono::system_clock::now();

    std::vector <std::thread> threads;
    for (int i = 0; i < matrix1.size(); i += threadsPerCore) {
        if (i >= matrix1.size() - threadsPerCore) {
//            std::cout << i << " " << matrix1.size() << std::endl;
            threads.emplace_back(multithreading, i, matrix1.size());
            break;
        } else {
//            std::cout << i << " " << i+threadsPerCore << std::endl;
            threads.emplace_back(multithreading, i, i+threadsPerCore);
        }

    }

    for (auto& t : threads) {
        t.join();
    }

//    printMatrix(resultMatrix);

    end = std::chrono::system_clock::now();
    elapsed = (end - begin);
    std::cout << "Multithreading time: " << elapsed.count() << " s\n";

    return 0;
}

void matricesMultiplication(const std::vector <std::vector <int>> matrix1, const std::vector <std::vector <int>> matrix2) {
    std::vector <std::vector <int>> result = {};

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

//    printMatrix(result);
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