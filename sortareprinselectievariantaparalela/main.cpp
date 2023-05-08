


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Utils.h"
 

#include <fstream>
#include <algorithm>
#include <mpi.h>


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


    int main(int argc, char* argv[]) {
        int size, rank;
        double start_time, end_time, total_time;
        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        int n;
        long* arr = NULL;

        if (rank == 0) {
            ifstream infile("test5.txt");
            if (!infile.is_open()) {
                cerr << "Error opening input file" << endl;
                MPI_Abort(MPI_COMM_WORLD, 1);
            }


            infile >> n;

            if (n <= 0) {
                cerr << "Invalid input size" << endl;
                MPI_Abort(MPI_COMM_WORLD, 1);
            }

            arr = new long[n];

            for (int i = 0; i < n; i++) {
                infile >> arr[i];
            }

            infile.close();
            start_time = MPI_Wtime();
        }

        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

        int chunk_size = n / size;
        long* chunk = new long[chunk_size];

        MPI_Scatter(arr, chunk_size, MPI_LONG, chunk, chunk_size, MPI_LONG, 0, MPI_COMM_WORLD);

       // quick_sort(chunk, 0, chunk_size - 1);
        selectionSort(chunk, chunk_size);

        MPI_Gather(chunk, chunk_size, MPI_LONG, arr, chunk_size, MPI_LONG, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            selectionSort(arr, n);
            end_time = MPI_Wtime();
            total_time = end_time - start_time;


            cout << "Time taken for sort process: " << total_time << " secods" << endl;
            cout << "Sorted vector: " << endl;
            for (int i = 0; i < n; i++) {
                cout << arr[i] << " ";
            }


            delete[] arr;
        }

        delete[] chunk;

        MPI_Finalize();
        return 0;
    }
