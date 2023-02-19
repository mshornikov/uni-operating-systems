#include <iostream>
#include <vector>
#include <random>
#include "header.h"

int main() {
    std::vector <std::vector <int>> matrix1 = matrixGenerator(3, 2);
    std::vector <std::vector <int>> matrix2 = matrixGenerator(2, 3);
    matricesMultiplication(matrix1, matrix2);

    return 0;
}

void matricesMultiplication(std::vector <std::vector <int>> matrix1, std::vector <std::vector <int>> matrix2) {
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

void printMatrix(std::vector <std::vector <int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector <std::vector <int>> matrixGenerator(int n, int m) {
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