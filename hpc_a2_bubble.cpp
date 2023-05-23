#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int MOD = 1e9+7;

using namespace std;

void bubbleSortSerial(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void bubbleSortParallel(int arr[], int n) {
    int i, j;
    #pragma omp parallel shared(arr,n) private(i,j)
    {
        #pragma omp for schedule(dynamic)
        for (i = 0; i < n - 1; i++) {
            for (j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j+1]) {
                    swap(arr[j], arr[j+1]);
                }
            }
        }
    }
}

int main() {
    int n = 10000;
    int arr1[n], arr2[n];
    clock_t start, end;
    double cpu_time_used;

    // Initialize the arrays with random values
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr1[i] = rand() % MOD;
        arr2[i] = arr1[i];
    }

    // Serial bubble sort
    start = clock();
    bubbleSortSerial(arr1, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Serial bubble sort time: " << cpu_time_used << " seconds" << endl;

    // Parallel bubble sort
    start = clock();
    bubbleSortParallel(arr2, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Parallel bubble sort time: " << cpu_time_used << " seconds" << endl;

    return 0;
}

