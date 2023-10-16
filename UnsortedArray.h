#ifndef UNORSORTED_H
#define UNORSORTED_H
#include <iostream>
#include <string>
using namespace std;
#define MAX_SIZE 10000 // Initial size of array

class UnsortedArray
{
	public:
		UnsortedArray();// Constructor
		virtual ~UnsortedArray();// Destructor
    //getters
		int getSize() const;
		int getCount(int) const;
		string getWord(int) const;
		string *&getPairs();
		virtual string getClass(); // Returns the name of the class

		void insert(string str); // Searches if the string exists, if not it adds it to the end of the array
		int search(string str) const; // Linear search (return count or -1, if the string  doesn't exist)
		int searchPos(string str) const; // Linear search, returns index or -1 (if argument not found)
		bool remove(string str); // Removes a string from the array and moves elements to maintain coherence
		bool reallocate(int n); // Changes the size of the array

		void print(int) const;

	protected:
		string *pairs; // Main array
		int items; // Items in array
		int maxSize = MAX_SIZE;
		int * count; // Array that saves the times a pair has been inserted

	private:
};
ostream &operator<<(ostream &, const UnsortedArray &);

#endif // UNORSORTED_H
