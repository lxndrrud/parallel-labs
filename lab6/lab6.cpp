#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> x{0}, y{0};

void thread1() {
    x.store(1, std::memory_order_relaxed); // (1)
    y.store(1, std::memory_order_release); // (2)
}

void thread2() {
    while (!y.load(std::memory_order_acquire)); // (4)
    std::cout << std::endl << x.load(std::memory_order_relaxed) << std::endl 
        << y.load(std::memory_order_acquire) << std::endl; // (5)
}

int main() {
    std::thread t1(thread1), t2(thread2);
    t1.join(), t2.join();
    return 0;
}
