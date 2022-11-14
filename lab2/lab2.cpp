#include <future>
#include <iostream>

int findMax(int a, int b ) {
    int check = a - b;
    if (check > 0) return a;
    else if (check < 0) return b;
    else return 0;
}
void generate(int i) {
    if (i % 2 == 0) {
        std::cout << std::endl << i << " " << findMax(i, i+3) << std::endl;
    } else {
        std::cout << std::endl << i << " " << findMax(i, i-1) << std::endl;
    }
}

void cycle(int from, int until) {
    for (int i = from; i < until; ++i) {
        std::future<void> ft = std::async (generate, i);
        ft.get();
    }
}
 
int main() {
    std::future<void>  ft1 = std::async (cycle, 100, 200);
    std::future<void>  ft2 = std::async (cycle, -200, -100);   

    ft1.get();
    ft2.get();

    return 0;
}