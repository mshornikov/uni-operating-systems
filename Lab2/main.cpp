#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include "header.h"

int number = 0;
std::mutex mt;

std::atomic<int> atomicNum = 0;

void increment() {
    number++;
}

void incrementMutex() {
    mt.lock();
    number++;
    mt.unlock();
}

void incrementAtomic() {
    atomicNum.fetch_add(1);
}

int main() {
    const int n = 1000;

    // 1
    auto begin = std::chrono::system_clock::now();

    std::vector <std::thread> threads;
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
        threads3.emplace_back(incrementAtomic);
    }

    for (auto& t : threads3) {
        t.join();
    }

    std::cout << number << std::endl;

    end = std::chrono::system_clock::now();
    elapsed = (end - begin);
    std::cout << "time #2: " << elapsed.count() << " s\n";
}