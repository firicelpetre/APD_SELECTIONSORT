


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Utils.h"

#include <fstream>
#include <algorithm>
#include <vector>
#include <thread>

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

void parallelSort(long arr[], int n, int numThreads) {
    vector<thread> threads;
    int chunkSize = n / numThreads;

    for (int i = 0; i < numThreads; i++) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? n : (i + 1) * chunkSize;
        threads.emplace_back(selectionSort, arr + start, end - start);
    }

    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    int n;
    long* arr = nullptr;

    ifstream infile("test5.txt");
    if (!infile.is_open()) {
        cerr << "Error opening input file" << endl;
        return 1;
    }

    infile >> n;
    if (n <= 0) {
        cerr << "Invalid input size" << endl;
        return 1;
    }

    arr = new long[n];
    for (int i = 0; i < n; i++) {
        infile >> arr[i];
    }
    infile.close();

    double start_time = clock();

    int numThreads = 4; // Numărul dorit de fire de execuție
    parallelSort(arr, n, numThreads);
    selectionSort(arr, n);

    double end_time = clock();
    double total_time = (end_time - start_time); 

    cout << "Time taken for sort process: " << total_time << " seconds" << endl;
    cout << "Sorted vector: " << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;

    return 0;
}

