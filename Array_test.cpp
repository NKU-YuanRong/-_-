#include <iostream>
#include <windows.h>
using namespace std;

// Array size
const int SIZE = 100000;

// Test round
const int ROUND = 5;

// Test Array
int com_arr[SIZE];

// Time cost
LARGE_INTEGER nFreq, nBeginTime, nEndTime;

void Test_array() {
    //Initializing
    QueryPerformanceFrequency(&nFreq);
    for (int i = 0; i < SIZE; i++) {
        com_arr[i] = i;
    }


    //Common algorithm:
    QueryPerformanceCounter(&nBeginTime);
    for (int k = 0; k < ROUND; k++) {
        int sum = 0;
        for (int i = 0; i < SIZE; i++) {
            sum += com_arr[i];
        }
    }
    QueryPerformanceCounter(&nEndTime);

    double time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
    cout << "Common algorithm: " << time / ROUND << endl;

    //Parallel algorithm(dual-link):
    QueryPerformanceCounter(&nBeginTime);
    for (int k = 0; k < ROUND; k++) {
        int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum = 0;
        for (int i = 0; i < SIZE; i += 2) {
            sum1 += com_arr[i];
            sum2 += com_arr[i + 1];
        }
        sum = sum1 + sum2;
    }
    QueryPerformanceCounter(&nEndTime);

    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
    cout << "Over algorithm: " << time / ROUND << endl;
}

int main()
{
    Test_array();
    return 0;
}