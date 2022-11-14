#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
 
std::map<std::string, std::string> g_pages;
bool flag;
std::mutex my_mutex;
 
void save_page(const std::string &url)
{
    while(true) {
        if (!flag) {
            flag = true;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            // имитация получения длинной страницы
            std::string result = "fake content";

            my_mutex.lock();
            //std::lock_guard<std::mutex> guard(my_mutex);
            g_pages[url] = result;
            my_mutex.unlock();
            flag = false;
            break;
        }
        
    }
    
}
 
int main() 
{
    std::thread t1(save_page, "http://foo");
    std::thread t2(save_page, "http://bar");
    t1.join();
    t2.join();
 
    for (const auto &pair : g_pages) {
        std::cout << pair.first << " => " << pair.second << '\n';
    }
}