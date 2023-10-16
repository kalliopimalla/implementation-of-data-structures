#ifndef HASHMAP_h
#define HASHMAP_h

#include <iostream>
#include <string.h>
using namespace std;

class HashMap
{
	public:

		HashMap(); // Constructor reserves space for Array and sets size=0
		~HashMap(); // Destructor destroys the hashmap

		int getSize() const;// Size getter
		string getClass(); // Returns the name of the class
		int getComparisons(); // Comparisons getter

    void resize(); // Doubles the size of the array
    int insert(string str); // Inserts a string in hashmap (returns the position)
    int search(string str); // Searches for a string in hashmap (returns the times str was inserted)

    void print(); // Prints the pairs in hashmap array with the times each one is shown

  private:
    string *hashmap; // Array with pairs based on hash function
    int *times; // Array storing the times its pair has been inserted
    int items; // Unique words
    int size; // Size of the hashmap array
    int comparisons_counter = 0; // Number of comparisons in order to evaluate the hash function

};
ostream &operator<<(ostream &, const HashMap &); // prints basic info about the array, like type (HashTable) and size (total words saved)
#endif
