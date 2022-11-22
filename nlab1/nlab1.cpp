#include <omp.h>
#include <bits/stdc++.h>
#include <iostream>

#define ROWS 3
#define COLS 3

void matrix_add(int A[ROWS][COLS], int B[ROWS][COLS]) {
    #pragma omp parallel for num_threads(2)
    for (int i = 0; i < ROWS; i++) {
        #pragma omp parallel for
        for (int j = 0; j < COLS; j++) {
            std::cout << std::setw(7) << A[i][j] << "+" << B[i][j] << "=" << A[i][j] + B[i][j];
        }
        std::cout << std::endl;
    }
}

int main() {
    int A[ROWS][COLS] = { 
        { 11, 22, 33},
        { 55, 26, 17},
        { 17, 18, 19}
    };

    int B[ROWS][COLS] = { 
        { 14, 13, 62},
        { 15, 27, 36},
        { 12, 14, 19}
    };
    matrix_add(A, B);

    return 0;
}
