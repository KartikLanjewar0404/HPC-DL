#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>

int MOD = 1e9+7;

using namespace std;
using namespace std::chrono;

void merge(int *arr, int left, int mid, int right)
{
    int *temp = new int[right - left + 1];

    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i - left];

    delete[] temp;
}

void merge_sort_serial(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        merge_sort_serial(arr, left, mid);
        merge_sort_serial(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void merge_sort_parallel(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                merge_sort_parallel(arr, left, mid);
            }

            #pragma omp section
            {
                merge_sort_parallel(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
    }
}

int main()
{
    int size = 1000000;
    int *arr_serial = new int[size];
    int *arr_parallel = new int[size];
    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        arr_serial[i] = rand() % MOD;
        arr_parallel[i] = arr_serial[i];
    }

    // serial merge sort
    auto start = high_resolution_clock::now();
    merge_sort_serial(arr_serial, 0, size - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Serial Time: " << duration.count() << " microseconds" << endl;

    // parallel merge sort
    start = high_resolution_clock::now();
    merge_sort_parallel(arr_parallel, 0, size - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Parallel Time: " << duration.count() << " microseconds" << endl;

    delete[] arr_serial;
    delete[] arr_parallel;

    return 0;
}

