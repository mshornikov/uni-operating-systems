#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include "header.h"

const int n = 1000000000;

int number = 0;
std::mutex mt;

std::atomic<int> atomicNum = 0;

void increment() {
    for (int i = 0; i < n; i++) {
        number++;
    }
}

void incrementMutex() {
    for (int i = 0; i < n; i++) {
        mt.lock();
        number++;
        mt.unlock();
    }
}

void incrementAtomic() {
    for (int i = 0; i < n; i++) {
        atomicNum.fetch_add(1);
    }
}

int main() {

    // 1
    auto begin = std::chrono::system_clock::now();

    std::vector <std::thread> threads;
    for (int i = 0; i < 8; i++) {
        threads.emplace_back(increment);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << number << std::endl;

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = (end - begin);
    std::cout << "time #1: " << elapsed.count() << " s\n";

    number = 0;

    // 2
    begin = std::chrono::system_clock::now();

    std::vector <std::thread> threads2;
    for (int i = 0; i < 8; i++) {
        threads2.emplace_back(incrementMutex);
    }

    for (auto& t : threads2) {
        t.join();
    }

    std::cout << number << std::endl;

    end = std::chrono::system_clock::now();
    elapsed = (end - begin);
    std::cout << "time #2: " << elapsed.count() << " s\n";

    // 3
    begin = std::chrono::system_clock::now();

    std::vector <std::thread> threads3;
    for (int i = 0; i < 8; i++) {
        threads3.emplace_back(incrementAtomic);
    }

    for (auto& t : threads3) {
        t.join();
    }

    std::cout << number << std::endl;

    end = std::chrono::system_clock::now();
    elapsed = (end - begin);
    std::cout << "time #3: " << elapsed.count() << " s\n";
}