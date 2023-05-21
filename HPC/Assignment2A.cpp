/*
Write a program to implement Parallel Bubble Sort and Merge sort using OpenMP. Use
existing algorithms and measure the performance of sequential and parallel algorithms
*/
// Bubble Sort
#include <iostream>
#include <omp.h>
using namespace std;

void bubble(int array[], int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (array[j] > array[j + 1]) swap(array[j], array[j + 1]);
        }
    }
}

void parallelBubbleSort(int arr[], int size) {
    bool swapped;
    for (int i = 0; i < size - 1; i++) {
        swapped = false;
        #pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                 swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90,55,3,66,96,9,3,9,3,9,3,9,44,55,666,01,233,36,3,6,6,6,6};
    int size = sizeof(arr) / sizeof(arr[0]);
    double start_time, end_time;

    cout << "Original array: ";
    for (int i = 0; i < size; i++) {
         cout << arr[i] << " ";
    }
    cout <<  endl;

    start_time = omp_get_wtime();
    parallelBubbleSort(arr, size);
    end_time = omp_get_wtime();
    cout << "Sequential Bubble Sort took : " << end_time - start_time << " seconds.\n";


    start_time = omp_get_wtime();
    bubble(arr, size);
    end_time = omp_get_wtime();
    cout << "Normal Bubble Sort took : " << end_time - start_time << " seconds.\n";

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
         cout << arr[i] << " ";
    }
    cout <<  endl;
    
    return 0;
}