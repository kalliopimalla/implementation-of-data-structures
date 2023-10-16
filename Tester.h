#include <iostream>
#include <fstream> // file handling
#include <string.h>
#include <time.h> // for srand function
#include <chrono> // for timing
#include <thread> // for timing

using namespace std;

#define BUF 1000
#define TEST_SIZE 10000 // Size of test subset Q

// Preprocessing of text file. Making uppercase letters
// to lowercase and making all whitespaces to spaces.
void pre_processing(string input, string output)
{

	char r;
  fstream f;
  fstream f_new;

  f.open(input, ios::in);
  f_new.open(output,ios::out);

	// Taking a file and making new file
	// only with lowercase alphabet letters and spaces.
  if(f.is_open())
  {
    while (!f.eof())
    {
      f >> std::noskipws>> r;
			if(!f.eof()){
				if((r>='A' && r<='Z') || (r>='a' && r<='z') || r == ' ' || r == '\n') // Getting characters that we need
				{
	        if (r == '\n') // Converting change of line characters to spaces to use a simple getline when getting pairs
					{
	          f_new << ' ';
	        }
					else if (r>='A' && r<='Z') // Making uppercase to lowercase letters
					{
	          r = 'a' + (r - 'A');
	          f_new << r;
	        }
	        else // If it's lowercase output it in the file
	        {
	          f_new << r;
	        }
      	}
			}
    }
    f.close();
    f_new.close();
  }
}

int create_array(string *&pairs, string input) // Creates an array with all the pairs as they come.
{
	ifstream f_last;
  string *pairs_temp = NULL;
  int i, distance, items=1;
  string s1, s2;

  f_last.open(input,ios::in);

  if (f_last.is_open()){
		pairs = new string[items]; // Allocating memory for the first pair

    while(!f_last.eof()){

			f_last >> std::ws; // Avoiding all whitespaces
			std::getline(f_last, s1, ' '); // Reading one word

			f_last >> std::ws; // Avoiding all whitespaces
			std::getline(f_last, s2, ' '); // Reading the next word

			pairs[items-1] = s1 + ' ' + s2; // Creating a pair with s1 and s2

			if(!f_last.eof()) {
				distance = (-1) * s2.length() -1; // Counting the length of the second word so as to go back after creating the pair to read it as the first word

				f_last.seekg(distance,ios_base::cur); // Moving input position indicator

				pairs_temp = new string[items]; // Allocating memory for pair_temp[]

				for(int i=0;i<items;i++) // Copying all objects of pair[] to pair_temp[]
				{
						pairs_temp[i] = pairs[i];
				}

				delete[] pairs;
				pairs = new string[++items]; // Allocating more memory to pair[]

				for(int i=0;i<items-1;i++) // Copying objects of pair_temp[] to the new pair[]
				{
						pairs[i] = pairs_temp[i];
				}

				delete[] pairs_temp;
				}
    }
    f_last.close();
  }

	return items;
}

void createQ(string *&pairs, int items, string *&test) // Creates a subset of TEST_SIZE random pairs
{
	int randpos;
	test = new string[TEST_SIZE];
	srand(time(0));
	for (int i=0;i<TEST_SIZE;i++)
		{
			randpos = rand() % items; // Gets a random position from 0 to items-1
			test[i] = pairs[randpos]; // Gets the string on the random position
		}
}

// Inserts all words from a file to  a data structure and prints the time needed in the output file
template <class X> void benchmarkInsertClock(X &datastructure, string filename, string output)
{
  int distance =0;
	string word1, word2, pair;

	ifstream file;
	file.open(filename, ios::in);
	ofstream out;
	out.open(output, ios::out|ios::app);

	out << "Creating "<< datastructure.getClass() << endl;

	auto start = std::chrono::high_resolution_clock::now(); // Saves the time where we start inserting pairs from the file

	if (file.is_open())
	{
		while(!file.eof()){

			file >> std::ws; // Avoiding all whitespaces
			std::getline(file, word1, ' '); // Reading one word

			file >> std::ws; // Avoiding all whitespaces
			std::getline(file, word2, ' '); // Reading the next word

			pair = word1 + ' ' + word2; // Creating a pair with word1 and word2


			if(!file.eof()) {
				distance = (-1) * word2.length() -1; // Counting the length of the second word so as to go back after creating the pair to read it as the first word
				file.seekg(distance,ios_base::cur); // Moving input position indicator
			}
			datastructure.insert(pair); // Inserting the pair in the data base
		}
		file.close();
	}

	auto end = std::chrono::high_resolution_clock::now(); // Saves the time were we finished inserting pairs
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // Calculating the duration it took to insert all pairs from the file

	// Printing in the file
	out << "Duration is " << duration.count() << " microseconds." << endl;
	out << endl;
	out.close();
}

template <class X> void benchmarkSearchClock(X &datastructure, string *&test, string filename) // Template function that counts the time it takes to search a set of pairs in a data structure
{
	ofstream output;
	output.open(filename, ios::out|ios::app);

	if(output.is_open())
	{
	  // Printing in the file
		output << "Searching Q subset in " << datastructure.getClass() << endl;

		auto start = std::chrono::high_resolution_clock::now(); // Saves the time where we start searching the pairs from a subset into a data structure

		for(int i=0;i<TEST_SIZE;i++)
		{
			output << test[i] << " -> " << datastructure.search(test[i]) << endl;
		}

		auto end = std::chrono::high_resolution_clock::now(); // Saves the time were we finished searching
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // Calculating the duration it took to search all pairs in a data structure

		// Printing in the file
		output << "Duration is " << duration.count() << " microseconds." << endl;
		output << endl;
	}
  output.close();
}
