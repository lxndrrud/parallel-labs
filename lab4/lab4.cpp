#include <iostream>
#include <chrono>
#include <ctime>
#include <future>

using namespace std;

void elementSwap(int* ele1, int* ele2) {
    int temp = *ele1;
    *ele1 = *ele2;
    *ele2 = temp;
}

int elementPartition (int array[], int less, int more) {
    int pivotelement = array[more];
    int indexSmaller = (less - 1);
    for (int qs = less; qs <= more - 1; qs++) {
        if (array[qs] < pivotelement) {
            indexSmaller++;
            elementSwap(&array[indexSmaller], &array[qs]);
        }
    }
    elementSwap(&array[indexSmaller + 1], &array[more]);
    return (indexSmaller + 1);
}

void demoquickSort(int array[], int less, int greater) {
    if (less < greater) {
        int parInd = elementPartition(array, less, greater);
        std::future<void> f1 = std::async(demoquickSort, array, less, parInd - 1);
        std::future<void> f2 = std::async(demoquickSort, array, parInd + 1, greater);
        f1.get();
        f2.get();
    }
}

int main() {
    cout << "Быстрая сортировка \n";
    int array[] = {35, 15, 90, 26, 87, 12, 5, 44, 23, 1};
    int arrsize = sizeof(array) / sizeof(array[0]);
    cout << "До сортировки : \n";
    int z;
    for (z = 0; z < arrsize; z++)
    cout << array[z] << " ";
    cout << endl;
    std::chrono::time_point<std::chrono::system_clock> start, end;
  
    start = std::chrono::system_clock::now();
    std::future<void> f = std::async(demoquickSort, array, 0, arrsize - 1);
    f.get();
    end = std::chrono::system_clock::now();

    cout << "После сортировки : \n";
    int i;
    for (i = 0; i < arrsize; i++)
    cout << array[i] << " ";
    cout << endl;

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  
    std::cout << "Вычислено в: " << std::ctime(&end_time)
              << "Заняло времени: " << elapsed_seconds.count() << "s\n";
    return 0;
}
