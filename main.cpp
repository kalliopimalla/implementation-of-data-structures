#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "Tester.h"
#include "UnsortedArray.h"
#include "SortedArray.h"
#include "BinaryTree.h"
#include "AVLtree.h"
#include "HashMap.h"

#define BUFF_SIZE 30

int main() {

	string filename1 = "Input.txt"; // The name of the file we want to run the program on
	string filename2 = "Processed.txt"; // Input file after preprocessing
	string filename3 = "Output.txt"; // Output file

	ofstream f; // Opening and closing the output file to delete all the contents
	f.open(filename3, ios::out);
	f.close();

// data structures
  UnsortedArray a;
  SortedArray b;
	BinaryTree c;
  AVLtree d;
	HashMap e;

	string *test = NULL; // Test subset Q

	pre_processing(filename1, filename2); // Preprocessing of filename1 file to filename2. Making uppercase letters to lowercase and making whitespaces to spaces.


 // Calling a template function to insert the pairs of words in a file to each data structure
	benchmarkInsertClock<UnsortedArray>(a, filename2, filename3);
	benchmarkInsertClock<SortedArray>(b, filename2, filename3);
	benchmarkInsertClock<BinaryTree>(c, filename2, filename3);
	benchmarkInsertClock<AVLtree>(d, filename2, filename3);
	benchmarkInsertClock<HashMap>(e, filename2, filename3);

	createQ(a.getPairs(), a.getSize(), test); // Creates test set Q from pairs array to test array

	// Calling a template function to search for the pairs in a test subset in each data structure
	benchmarkSearchClock<UnsortedArray>(a, test, filename3);
	benchmarkSearchClock<SortedArray>(b, test, filename3);
	benchmarkSearchClock<BinaryTree>(c, test, filename3);
	benchmarkSearchClock<AVLtree>(d, test, filename3);
  benchmarkSearchClock<HashMap>(e, test, filename3);

  return 0;
}
