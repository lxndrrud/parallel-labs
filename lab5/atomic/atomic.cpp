#include <atomic>
#include <cstdio>
#include <thread>

static std::atomic<int> foobar(8);
static std::atomic<bool> start(false);

int main() {
    std::thread t1 = std::thread([]{
        int records[10];
        while (!start.load());
        for (size_t i = 0; i < 10; ++i) {
            foobar.store(3);
            records[i] = foobar.load();
        }
        for (size_t j = 0; j < 10; ++j) {
            printf("t1 %zu - %d\n", j, records[j]);
        }
    });

    std::thread t2 = std::thread([]{
        int records[10];
        while (!start.load());
        for (size_t i = 0; i < 10; ++i) {
            foobar.store(6);
            records[i] = foobar.load();
        }
        for (size_t j = 0; j < 10; ++j) {
            printf("t2 %zu - %d\n", j, records[j]);
        }
    });
    start.store(true);

    t1.join();
    t2.join();
    return 0;
}