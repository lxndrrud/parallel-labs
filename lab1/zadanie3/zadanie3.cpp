#include <thread>
#include <string>
#include <iostream>
#include <chrono>


void printSomething(std::string something) {
    std::this_thread::sleep_for(std::chrono::microseconds(2));
    std::cout << something << std::endl;
}

int main() {
    std::thread t1(printSomething, "Раз-два");
    std::thread t2(printSomething, "Три-четыре");

    t1.join();
    t2.join();
}

