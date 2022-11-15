#include <atomic>
#include <cstdio>

struct Counter {

    Counter(): count(0) {}

    std::atomic<unsigned> count;

    unsigned operator++(int) {
        return count.fetch_add(1);
    }

    unsigned operator--(int) {
        return count.fetch_sub(1);
    }
};


int main() {
    Counter a;
    printf("%u\n", a++);
    printf("%u\n", a++);
    printf("%u\n", a--);
    printf("%u\n", a--);
    return 0;
}