#include "Utils.h"

void test_generator() {
	ofstream fout("test5.txt");
	srand((unsigned)time(NULL));
	fout << 10000 << endl;
	for (int i = 0; i < 10000; i++) {
		fout << rand() % 1000000 + 1 << " ";
	}
	fout.close();
}


void load_test(long number[], int* dim) {
	int iterator = 0;
	ifstream fin("test5.txt");
	fin >> *dim;
	while (fin >> number[iterator]) {
		iterator++;
	}
}

 
