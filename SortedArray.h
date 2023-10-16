#ifndef SORTEDARRAY_H
#define SORTEDARRAY_H
#include "UnsortedArray.h"
#include <iostream>
#include<string.h>
using namespace std;

class SortedArray:public UnsortedArray
{
    public:
        //SortedArray();
        //virtual ~SortedArray();
         // uses remove, constructor and destructor functions from superclass (UnsortedArray)

			virtual string getClass(); // Returns the name of the class

			void insert(string); // Inserts a string in the array
      bool searchForInsertion(string, int&) const; // Finds the position to insert a string using binary search (return false, if the string doesn't exist)
      int search(string) const; // Binary Search for a string (return the times it's been inserted or -1 if it doesn't exist)

			void print(int) const; // Prints the array

    protected:

    private:
};
ostream &operator<<(ostream &, const SortedArray &);
#endif // SORTEDARRAY_H
