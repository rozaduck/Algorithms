// Mergesort 
// Mon 27/08/2018
// Stephanie Seymour 

using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>

int array[200];
int arraySize;

void mergeSort(int left, int right);
void merge(int left, int centre, int right);

int main() {
	// Hardcoded filename: 
	char filename[] = "ints.txt";
	cout << "Opening file " << filename << "...\n";
	// Try to open file 
	ifstream fin;
	fin.open(filename); 
	if (!fin.good()) {
		cout << "File ''" << filename << "'' cannot be opened.\nExiting program.\n"; 
		return -1; 
	}
	
	int input;
	fin >> input;
	while (!fin.eof()) {
		array[arraySize] = input; 
		arraySize++;
		fin >> input; 
	}
	
	fin.close(); 
	
	// Output array 
	cout << "Array before sorting: \n";
	for (int i=0; i<arraySize; i++) {
		cout << setw(5) << array[i] << " "; 
		if (i%10 == 9) 
			cout << "\n"; 
	}
	cout << "\n";
	
	// Mergesort the array 
	mergeSort(0, arraySize-1); 
	
	// Output array 
	cout << "Array after sorting: \n";
	for (int i=0; i<arraySize; i++) {
		cout << setw(5) << array[i] << " "; 
		if (i%10 == 9) 
			cout << "\n"; 
	}
	cout << "\n";
	
	return 0;
}

void mergeSort(int left, int right) {
	if (left < right) {
		int centre = (left +right) /2; 
//		cerr << "Splitting at " << centre << ".\n"; 
//		cerr << "Sorting left side...\n";
		mergeSort(left, centre); 
//		cerr << "Sorting right side...\n";
		mergeSort(centre+1, right); 
//		cerr << "Merging...\n";
		merge(left, centre, right); 
//		cerr << "\n";
	}
}

void merge(int left, int centre, int right) {
//	cerr << "Left:" << left << ", centre:" << centre << ", right:" << right << "\n"; 
	// Arrays to be merged are: 
//	cerr << "Merging arrays:\n";
	// A: left...centre [0...a-1]
//	cerr << "A: "; 
//	for (int i=left; i<=centre; i++) {
//		cerr << setw(5) << array[i] << " ";
//	}
//	cerr << "\n";
	// B: centre+1...right [0...b-1] 
//	cerr << "B: "; 
//	for (int i=centre+1; i<=right; i++) {
//		cerr << setw(5) << array[i] << " ";
//	}
//	cerr << "\n"; 
	// C: left...right in temp array [0...a+b-1] 
	int temp[right-left+1];
//	cerr << "Size of new array: " << right-left+1 << ".\n";
	
	int Apos = left, Bpos = centre +1;
	int merged = 0; 
	// Merge the two arrays until run out of one 
	while (Apos <= centre && Bpos <= right) {
		if (array[Apos] < array[Bpos]) {
			temp[merged] = array[Apos]; 
			Apos++; merged++; 
		}
		else {
			temp[merged] = array[Bpos]; 
			Bpos++; merged++;
		} 
	}
	// Add in the leftovers from the larger array 
	while (Apos <= centre) {
		temp[merged] = array[Apos]; 
		Apos++; merged++; 
	}
	while (Bpos <= right) {
		temp[merged] = array[Bpos]; 
		Bpos++; merged++; 
	}
	
//	cerr << "Merged array:\n";
	// Copy the temp array to the real array 
	for (int i=left, j=0; i<=right; i++, j++) {
		array[i] = temp[j];
		cerr << setw(5) << array[i] << " ";
	}
//	cerr << "\n";
}
