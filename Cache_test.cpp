#include<iostream>
#include <windows.h>
using namespace std;

// The size of matrix
const int SIZE = 20000;

// The round we test
const int ROUND = 5;

// Time counters
LARGE_INTEGER t_Frequency, t_Begin, t_End;

// Useless matrix, to clear the cache
const int CLEAR_SIZE = 1500;
int useless[CLEAR_SIZE][CLEAR_SIZE];

int sum[SIZE];
int b[SIZE][SIZE], a[SIZE];
void Test_Cache() {
    QueryPerformanceFrequency(&t_Frequency);

    //Initialize matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            b[i][j] = i + j;
        }
        a[i] = i;
    }

    // Clear the cache
    for (int i = 0; i < CLEAR_SIZE; i++) {
        for (int j = 0; j < CLEAR_SIZE; j++) {
            useless[i][j] = i + j;
        }
    }

    //Common algorithm:
    QueryPerformanceCounter(&t_Begin);
    for (int k = 0; k < ROUND; k++) {
        for (int i = 0; i < SIZE; i++) {
            sum[i] = 0;
            for (int j = 0; j < SIZE; j++) {
                sum[i] += b[j][i] * a[j];
            }
        }
    }
    QueryPerformanceCounter(&t_End);
    double time = (double)(t_End.QuadPart - t_Begin.QuadPart) / (double)t_Frequency.QuadPart;
    cout << "Common algorithm: " << time / ROUND << endl;

    //Parallel algorithm(cache optimized)
    QueryPerformanceCounter(&t_Begin);
    for (int k = 0; k < ROUND; k++) {
        for (int i = 0; i < SIZE; i++)
            sum[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE; i++) {
                sum[i] += b[j][i] * a[j];
            }
        }
    }
    QueryPerformanceCounter(&t_End);
    time = (double)(t_End.QuadPart - t_Begin.QuadPart) / (double)t_Frequency.QuadPart;
    cout << "Cache algorithm: " << time / ROUND << endl;
}

int main() {
    Test_Cache();
    return 0;
}