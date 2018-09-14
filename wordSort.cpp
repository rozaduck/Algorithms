// CSCI203 Assignment 1
// Mon 27/08/2018 
// Stephanie Seymour, ss465 

using namespace std; 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>

struct Node {
	string word; 
	int freq;
	Node* leftChild;
	Node* rightChild; 
};

// Program can handle up to 50k unique words 
Node array[50000]; 
int arraySize = 0; 

string prep(string word);
Node* insertRoot(string newWord);  
void insertNode(string newWord, Node* node); 
void mergeSort(int left, int right);
void merge(int left, int centre, int right);

// Unused outside debugging 
void visit(Node* node); 

int main() {
	// Prompt user for file name 
	char filename[20]; 
	cout << "Enter input filename: "; 
	cin >> filename; 
	// TESTING hardcoded filename: 
//	char filename[] = "data.txt";
	cout << "Opening file " << filename << "...\n";
	// Try to open file 
	ifstream fin;
	fin.open(filename); 
	if (!fin.good()) {
		cout << "File '" << filename << "' cannot be opened.\nExiting program.\n"; 
		return -1; 
	}
	
	// Establish the root of the BST 
	string input, newWord;
	fin >> input; 
	newWord = prep(input); 
	Node* root = insertRoot(newWord); 
	
	// Add each word to BST (if not in BST already) 
	while (!fin.eof()) {
		fin >> input; 
		// Preprocess each word before adding to BST 
		newWord = prep(input); 
		insertNode(newWord, root);
	}
	
	fin.close(); 
	
	// Mergesort the array (by frequency) 
	mergeSort(0, arraySize-1);
	
	// Output bottom ten 
	cout << "\nLeast frequent words:\n";
	for (int i=0; i<10; i++) {
		cout << "\t" << array[i].word << "(" << array[i].freq << ")\n";
	}
	
	// Output top ten 
	cout << "\nMost frequent words:\n";
	for (int i=arraySize-1; i>=(arraySize-10); i--) {
		cout << "\t" << array[i].word << "(" << array[i].freq << ")\n";
	}
	
	return 0;
}

string prep(string word) {
	// Convert to all lowercase 
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	// Strip punctuation from the word 
	for (int i = 0; i <= word.length(); i++) {
		if (ispunct(word[i])) {
   			word.erase(i--, 1);
		}
	}
	return word;
}

Node* insertRoot(string newWord) {
	// Put the root in the array 
	Node* root = &array[0];
	// Set the Node values 
	root->word = newWord; 
	root->freq = 1; 
	root->leftChild = NULL; 
	root->rightChild = NULL;
	return root; 
}

void insertNode(string newWord, Node* node) {
	Node* next = node; // This is the node we are inserting relative to 
//	cerr << "Inserting " << newWord << " after node " << node->word << "...\n";
	bool left; 
	
	if (newWord == node->word) {
//		cerr << newWord << " is already in tree.\n";
		node->freq++;
		return; // data is already in tree 
	}
	else if (newWord.compare(node->word) < 0) {
		next = node->leftChild; 
		left = true;
	}
	else if (newWord.compare(node->word) > 0) {
		next = node->rightChild; 
		left = false; 
	}
	
	if (next != NULL) {
		// If next node isn't empty, insert relative to next node 
		insertNode(newWord, next); 
	}
	else {
//		cerr << "Node is a leaf; inserting " << newWord << " here.\n";
		// Put data in node in the next space in the array 
		arraySize++; 
		next = &array[arraySize]; 
		// Set Node values 
		next->word = newWord; 
		next->freq = 1;
		next->leftChild = NULL; 
		next->rightChild = NULL; 
		
		// Set parent node pointer 
		if (left) {
			node->leftChild = next; 
		}
		else {
			node->rightChild = next; 
		}
	}
}

void visit(Node *node) { 
	// In-order traversal is an alphabetical sort 
	if (node->leftChild != NULL) {
		visit(node->leftChild); 
	}
	
	cout << node->word << "(" << node->freq << ")\n"; 
	
	if (node->rightChild != NULL) {
		visit(node->rightChild);
	}
}

void mergeSort(int left, int right) {
	if (left < right) {
		int centre = (left +right) /2; 
		mergeSort(left, centre); 
		mergeSort(centre+1, right); 
		merge(left, centre, right); 
	}
}

void merge(int left, int centre, int right) {
	// Arrays to be merged are: 
	// A: left...centre 
	// B: centre+1...right 
	// into left...right in temp array [0...a+b-1] 
	Node temp[right-left+1];
	
	int Apos = left, Bpos = centre +1;
	int merged = 0; 
	// Merge the two arrays until run out of one 
	while (Apos <= centre && Bpos <= right) {
		if (array[Apos].freq < array[Bpos].freq) {
			temp[merged] = array[Apos]; 
			Apos++; merged++; 
		}
		else if (array[Apos].freq > array[Bpos].freq) {
			temp[merged] = array[Bpos]; 
			Bpos++; merged++;
		} 
		// If the frequencies are equal, sort alphabetically 
		else if (array[Apos].freq == array[Bpos].freq){
			if (array[Apos].word.compare(array[Bpos].word) < 0) {
				temp[merged] = array[Apos]; 
				Apos++; merged++; 
			}
			else {
				temp[merged] = array[Bpos]; 
				Bpos++; merged++;
			}
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
	
	// Copy the temp array to the real array 
	for (int i=left, j=0; i<=right; i++, j++) {
		array[i] = temp[j];
	}
}
