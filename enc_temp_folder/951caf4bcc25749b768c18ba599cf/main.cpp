


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Utils.h"

using namespace std;

void selectionSort(long arr[], int n) {
    int i, j, minIndex, tmp;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        if (minIndex != i) {
            tmp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = tmp;
        }
    }
}

int main() {
     int n ;
    long arr[10000];
    test_generator();
    load_test(arr, &n);
    
   
    
    auto start = chrono::steady_clock::now();
    selectionSort(arr, n);
    auto end = chrono::steady_clock::now();
    
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    cout << "Time for sort process: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
    return 0;
}