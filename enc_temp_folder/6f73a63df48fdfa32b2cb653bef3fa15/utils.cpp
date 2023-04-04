#include "Utils.h"

void test_generator() {
	ofstream fout("test6.txt");
	srand((unsigned)time(NULL));
	fout << 10000 << endl;
	for (int i = 0; i < 100000; i++) {
		fout << rand() % 1000000 + 1 << " ";
	}
	fout.close();
}


void load_test(long number[], int* dim) {
	int iterator = 0;
	ifstream fin("test6.txt");
	fin >> *dim;
	while (fin >> number[iterator]) {
		iterator++;
	}
}

 
