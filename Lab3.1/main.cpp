#include <iostream>
#include <semaphore.h>
#include <thread>
#include <fstream>
#include <string>
#include <vector>
#include <fcntl.h>

sem_t* semaphore1;
sem_t* semaphore2;

void reader() {
    while(true) {
        sem_wait(semaphore2);

        std::ifstream in("/Users/mshornikov/CLionProjects/uni-operating-systems/Lab3.1/chat.txt");
        std::string lastline;

        if (in.is_open()) {
            std::string line;
            while (std::getline(in, line)) {
                lastline = line;
//               std::cout << line << std::endl;
            }
            std::cout << lastline << std::endl;
        }
        sem_post(semaphore2);
//        in.close();
    }
}

void writer() {
    while(true) {
        sem_wait(semaphore1);

        std::string text;
        std::ofstream outfile("/Users/mshornikov/CLionProjects/uni-operating-systems/Lab3.1/chat.txt", std::ios::app);
        if (outfile.is_open()) {
            std::cin >> text;
            if (text == "0") {
                sem_close(semaphore1);
                sem_close(semaphore2);
                sem_unlink("/my_semaphore1");
                sem_unlink("/my_semaphore2");
                exit(0);
            }
            outfile << "User 1: " << text << std::endl;
        }
        outfile.close();
        sem_post(semaphore1);
    }
}

int main() {
    // Create named semaphore with initial value 1
    semaphore1 = sem_open("/my_semaphore1", O_CREAT, S_IRUSR | S_IWUSR, 1);
    semaphore2 = sem_open("/my_semaphore2", O_CREAT, S_IRUSR | S_IWUSR, 1);

    // Create worker thread
    std::thread t1(writer);
    std::thread t2(reader);

    // Main thread waits for worker thread to finish
    t1.join();
    t2.join();

    sem_close(semaphore1);
    sem_close(semaphore2);
    sem_unlink("/my_semaphore1");
    sem_unlink("/my_semaphore2");
    return 0;
}