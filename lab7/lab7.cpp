#include <thread>
#include <atomic>
#include <cassert>
#include <string>
#include <iostream>
 
std::atomic<std::string*> ptr;
 
void producer() {
    std::string* p  = new std::string("Hello");
    std::cout << "Значение отправленных данных: " << *p << std::endl;
    ptr.store(p, std::memory_order_release);
}
 
void consumer() {
    std::string* p2;
    while (!(p2 = ptr.load(std::memory_order_consume))) ;
    std::cout << "Значение полученных данных: " << *p2 <<std::endl;     
}
 
int main() {
    std::thread t1(producer), t2(consumer);
    t1.join(), t2.join();
    return 0;
}