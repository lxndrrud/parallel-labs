#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
 
std::map<std::string, std::string> g_pages;
std::mutex my_mutex;
std::condition_variable data_cond;

// Вызов опопвещения condition_variable
void notify() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    data_cond.notify_one(); // (3)
}
 
// Без condition_variable
void save_page1(const std::string &url)
{
    // имитация получения длинной страницы
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string result = "fake content";
 
    std::lock_guard<std::mutex> guard(my_mutex);
    g_pages[url] = result;
}

// С ожиданием condition_variable 
void save_page2(const std::string &url)
{
    // имитация получения длинной страницы
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string result = "fake content";
    
    std::unique_lock<std::mutex> lk(my_mutex);


    data_cond.wait(lk, [result, url] { g_pages[url] = result; return true; });
}
 
int main() 
{
    std::thread t1(save_page1, "http://foo");
    std::thread t2(save_page2, "http://bar");
    std::thread t3(notify);

    t1.join();
    t2.join();
    t3.join();
 
    for (const auto &pair : g_pages) {
        std::cout << pair.first << " => " << pair.second << '\n';
    }
}